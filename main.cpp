#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <sstream> 
#include <sys/sysinfo.h>
#include "shape.h"
#include "tuple.h"
#include "ray.h"
#include "sphere.h"
#include "cube.h"
#include "cylinder.h"
#include "cone.h"
#include "plane.h"
#include "light.h"
#include "world.h"
#include "hitList.h"
#include "matrix.h"
#include "camera.h"
#define EPSILON 0.0001
#define REMAIN 2

int width,height,fieldview,objects;
bool shadows,reflections,refractions,precision,vector;
int from[3];
int to[3];
int up[3];
world sceneWorld;
camera worldCamera;
struct Thread_Positions
{
     int start;
     int end;
     int tid;
     tuple * tuplelist;
};


float schlick(float & cos, const float& n1, const float& n2, const float& sin2_t ){
	if (n1 > n2){
		if (sin2_t>1.0){
			return 1.0;
		}
		float cos_t = sqrt(1.0-sin2_t);
		cos=cos_t;
	}
	float r_0= pow(((n1-n2)/(n1+n2)),2);
	return r_0+(1-r_0)*pow((1-cos),5);
}
tuple color(const ray& r, int remain,std::list<shape*> *containers);
tuple lighting(const material& input_material, const light& input_light, const tuple& point,
				const tuple& eyev, const tuple& normalv, const bool& isShadow, const float& transparency){
	tuple effective_color= input_material.color*input_light.intensity;
	tuple lightv= unit_vector(input_light.position-point);
	tuple ambient= effective_color*input_material.ambient;
	float light_dot_normal= dot(lightv,normalv);
	tuple diffuse;
	tuple specular;
	if(isShadow){
		return tuple(0,0,0,1);
	}
	if (light_dot_normal < 0){
		diffuse=tuple(0,0,0,1);
		specular=tuple(0,0,0,1);
	}
	else{
		//compute diffuse contribution
		diffuse= effective_color*input_material.diffuse*light_dot_normal;
		//reflect_dot_eye represents cosine of the angle
		//between the reflection vector and the eye vector
		//a negative number means light reflects away from the eye
		tuple reflectv=reflect(negate_tuple(lightv),normalv);
		float reflect_dot_eye= dot(reflectv,eyev);
		if (reflect_dot_eye<=0){
		 	specular=tuple(0,0,0,1);
		}
		else{
		 	float factor= pow (reflect_dot_eye,input_material.shininess);
		 	specular= input_light.intensity*input_material.specular*factor;
		}
	}

	/*`std::cout << light_dot_normal << " light_dot_normal \n";
	std::cout << lightv.x() << " " << lightv.y() << " " << lightv.z() << " light \n";
	std::cout << normalv.x() << " " << normalv.y() << " " << normalv.z() << " normal \n";
	std::cout << ambient.x() << " " << ambient.y() << " " << ambient.z() << " ambient \n";
	std::cout << diffuse.x() << " " << diffuse.y() << " " << diffuse.z() << " diffuse \n";
	std::cout << specular.x() << " " << specular.y() << " " << specular.z() << " specular \n";*/
	//std::cout << input_material.color.x() << " " << input_material.color.y() << " " << input_material.color.z() << " color \n";

	return ambient+specular+diffuse;
}
ray rayforPixel(const camera& inputCam, int& px, int& py){
	float xoffset = (px+0.5)*inputCam.pixelSize;
	float yoffset = (py+0.5)*inputCam.pixelSize;
	float worldx = inputCam.halfWidth - xoffset;
	float worldy = inputCam.halfHeight - yoffset;
	matrix invCamera= invertMatrix(inputCam.cameraTransform);
	tuple pixel=  tuple(worldx,worldy,-1,1)*invCamera;
	tuple origin = tuple(0,0,0,1)*invCamera;
	//normalize 
	tuple direction = unit_vector(pixel-origin);
	return ray(origin,direction);
}
tuple reflectedworld(float& objectReflectance, tuple& reflectv,tuple& overPoint, int remain,std::list<shape*> *containers){

	if (objectReflectance==0 || remain<=0){
		return tuple(0,0,0,1);
	}
	else{
		ray reflect_ray(overPoint,reflectv);
		tuple reflectColor;
		reflectColor = color(reflect_ray, remain-1,containers); 

		return reflectColor*objectReflectance;
	}
	
}
void setRefractiveIndexes(std::list<shape*> *containers, float* n1, float* n2,  shape* objectShape){
	*n1=1.0;
	*n2=1.0;
	std::list<shape*>::iterator it;
	if(	containers->size() ==0){
		*n1=1.0;
	}
	else{
		*n1=(containers->back())->shapeMaterial.refractionIndex;
	}
	//std::cout << containers->size() << "Tamano \n";
	bool present=false;
	for (it = containers->begin(); it != containers->end(); ++it){
		if(objectShape==*(it)){
			containers->remove(objectShape);
			present=true;
			break;
		}
	}
	if (present==false){
		containers->push_back (objectShape);
	}
	//std::cout << containers->size()  << "Tamano \n";
	if(containers->size() ==0){
		*n2=1.0;
	}
	else{
		*n2=(containers->back())->shapeMaterial.refractionIndex;	
	}
	//std::cout << *n1 << " " << *n2  << "\n";

}
tuple refractedworld(tuple& underPoint, tuple& normalv, tuple& eyev,
					 float& transparency, float& nratio,
					 float& sin2_t, float& cos_i,int remain, std::list<shape*> *containers){
	if(transparency==0 || remain<=0){
		return tuple(0,0,0,1);
	}
	else{
		float cos_t = sqrt(1.0-sin2_t);
		tuple direction= normalv*(nratio*cos_i-cos_t)-eyev*nratio;
		ray refactRay(underPoint,direction);
		return color(refactRay,remain-1,containers)*transparency;
	}
}
bool isPointShadow(const tuple& inputPoint, const int remain){
	tuple v = sceneWorld.sourceLight.position-inputPoint;
	float distance = v.length();
	tuple direction = unit_vector(v);
	ray r(inputPoint,direction);
	int it;
	//TODO REMOVE REPLICATED CODE
	float nearHitPoint = std::numeric_limits<float>::max(); //set to infinity
	float returnedHitPoint;
	int objectPoistion;
	for (it = 0; it <objects; it++){

		returnedHitPoint=(sceneWorld.objectsInWorld[it])->ray_hits_me(r,nearHitPoint);
		if(returnedHitPoint<nearHitPoint){
			objectPoistion=it;
			nearHitPoint=returnedHitPoint;
		}
		
	}
	if(nearHitPoint!=std::numeric_limits<float>::max()){
		material nearHitPointMaterial= (sceneWorld.objectsInWorld[objectPoistion])->shapeMaterial;
		tuple position=r.point_at_parameter(nearHitPoint);
		tuple rdir=r.direction();
		tuple over_point= position+(rdir*EPSILON);
		if(nearHitPoint<distance){
			if(remain!=0){
				if (nearHitPointMaterial.transparency!=0){
					return isPointShadow(over_point, remain-1);
				}
				else{
					return true;
				}
			}
			else{
				return false;
			}
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}

}
//TODO THIS SHOULD BE A WORLD FUNCTION
tuple color(const ray& r, int remain,std::list<shape*> *containers){
	int it;
	//TODO REMOVE REPLICATED CODE
	float nearHitPoint = std::numeric_limits<float>::max(); //set to infinity
	float returnedHitPoint;

	int objectPoistion;
	for (it = 0; it <objects; it++){

		returnedHitPoint=(sceneWorld.objectsInWorld[it])->ray_hits_me(r,nearHitPoint);
		if(returnedHitPoint<nearHitPoint){
			objectPoistion=it;
			nearHitPoint=returnedHitPoint;
		}
		
	}
	if(nearHitPoint!=std::numeric_limits<float>::max()){
		material nearHitPointMaterial= (sceneWorld.objectsInWorld[objectPoistion])->shapeMaterial;
		tuple position=r.point_at_parameter(nearHitPoint);
		tuple rdir=r.direction();
		//Define surface normal
		tuple normalv=(sceneWorld.objectsInWorld[objectPoistion])->normal_at(position);
		//In case normal points away from eye vector
		tuple eyev;
		eyev=negate_tuple(rdir);
		/*std::cout << r.origin().x() << " " << r.origin().y() << " " << r.origin().z() << " origin \n";
		std::cout << rdir.x() << " " << rdir.y() << " " << rdir.z() << " rdir \n";
		std::cout << nearHitPoint << " hit point\n";
		std::cout << position.x() << " " << position.y() << " " << position.z() << " position \n";
		std::cout << normalv.x() << " " << normalv.y() << " " << normalv.z() << " normalv \n";
		std::cout << eyev.x() << " " << eyev.y() << " " << eyev.z() << " eyev \n";
		std::cout << dot(normalv,eyev) << " dot eyev\n";
		std::cout << dot(normalv,rdir) << " dot rdir\n";*/
		if(dot(normalv,eyev)<0){
			normalv=negate_tuple(normalv);

		}
		tuple reflectv= reflect(rdir,normalv);
		tuple over_point= position+(normalv*EPSILON);
		tuple under_point= position-(normalv*EPSILON);
		float n1;
		float n2;
		setRefractiveIndexes(containers, &n1, &n2, (sceneWorld.objectsInWorld[objectPoistion]));
		float nratio=n1/n2;
		float cos_i=dot(eyev,normalv);
		float sin2_t=pow(nratio,2)*(1-pow(cos_i,2));

		/*End Comps*/
		/*Shade Hit function*/
		bool isShadow=false;
		if (shadows){
			isShadow=isPointShadow(over_point,5);
		}
		tuple color= lighting(nearHitPointMaterial, sceneWorld.sourceLight,over_point,eyev, normalv,isShadow,nearHitPointMaterial.transparency);
		/*std::cout << color.x() << " " << color.y() << " " << color.z() << " color \n";
		std::cout << reflectv.x() << " " << reflectv.y() << " " << reflectv.z() << " reflectv \n";
		std::cout << over_point.x() << " " << over_point.y() << " " << over_point.z() << " over_point \n";*/

		tuple refractedColor;
		if(refractions){
			refractedColor=refractedworld(under_point, normalv,eyev,nearHitPointMaterial.transparency,
											nratio,sin2_t,cos_i, remain,containers);
		}
		else{
			refractedColor=tuple(0,0,0,0);
		}
		tuple reflectedColor;
		if(reflections){
			reflectedColor=reflectedworld( nearHitPointMaterial.reflective, reflectv, over_point,remain, containers);
		}
		else{
			reflectedColor=tuple(0,0,0,0);
		}
		if(nearHitPointMaterial.reflective>0 && nearHitPointMaterial.transparency>0){
			float reflectance = schlick(cos_i, n1, n2,sin2_t);
			return color+refractedColor*(1-reflectance)+reflectedColor*reflectance;
		}
		else{
			return color+refractedColor+reflectedColor;	
		}

	}
	return tuple(0.0,0.0,0.0,1.0);
}
void *thread_renderWorld(void *arg)
{
    struct Thread_Positions *localp;
    localp =(struct Thread_Positions*) arg;
   	localp->tuplelist=(tuple*)malloc((localp->end-localp->start)*sizeof(tuple));
    cpu_set_t cpuset;
    // CPU_ZERO: This macro initializes the CPU set set to be the empty set.
    CPU_ZERO(&cpuset);
    // CPU_SET: This macro adds cpu to the CPU set set.
    CPU_SET(localp->tid, &cpuset);
    const pthread_t pid = pthread_self();
    // pthread_setaffinity_np: The pthread_setaffinity_np() function sets the CPU affinity mask of the thread thread to the CPU set pointed to by cpuset. If the call is successful, and the thread is not currently running on one of the CPUs in cpuset, then it is migrated to one of those CPUs.
    const int set_result = pthread_setaffinity_np(pid, sizeof(cpu_set_t), &cpuset);
	int j,i,k;
	//worldCamera.vsize
	//worldCamera.hsize
	/*std::cout << i << " "  << "\n";
	std::cout << j << " "  << "\n";
	std::cout << localp->tid << " "  << "\n";*/

	int pos=0;
	for (j=localp->start/width;j<localp->end/width;j++){
		for(i=localp->start%width;i <worldCamera.hsize;i++){
			ray r= rayforPixel(worldCamera, i, j);
			std::list<shape*> containers;
			tuple col = color(r,REMAIN, &containers);
			localp->tuplelist[pos]=col;
			pos++;
		}
	}

    return NULL;
}
void renderWorld(){
    pthread_t *ptr;
    Thread_Positions *pthreadinfo;
    int i=0;
    int threads_to_spawn= get_nprocs_conf();
    ptr = (pthread_t*)malloc(threads_to_spawn*sizeof(pthread_t));
    pthreadinfo = (Thread_Positions*)malloc(threads_to_spawn*sizeof(Thread_Positions));
    int chunk = (width*height)/threads_to_spawn;
    int start=0;
    int end=0;
    while(start<(width*height)){
        struct Thread_Positions p1;
        pthreadinfo[i].start=start;
        pthreadinfo[i].end=start+chunk;
        pthreadinfo[i].tid=i;  
        pthread_create(&ptr[i], NULL, thread_renderWorld, &pthreadinfo[i]);
        start+=chunk;
        i++;

    }
           
    for(i = 0; i < threads_to_spawn; i++)
        pthread_join(ptr[i], NULL);
    for(i=0;i< threads_to_spawn;i++){
    	for(start=0;start<chunk;start++){
	    	int ir = int(255.99*pthreadinfo[i].tuplelist[start].r()); 
			int ig = int(255.99*pthreadinfo[i].tuplelist[start].g()); 
			int ib = int(255.99*pthreadinfo[i].tuplelist[start].b()); 
			std::cout << ir << " " << ig << " " << ib << "\n";
    	}
    }
    free(pthreadinfo);
    free(ptr);  
}



void startWorld(){
		//CREATE camera
	// with fieldview of pi/2
	std::cout << "P3\n" << width << " "<< height << "\n255\n";
	worldCamera.setCamera(width,height,M_PI/fieldview);
	tuple from_t(from[0],from[1],from[2],1);
	tuple to_t(to[0],to[1],to[2],1);
	tuple up_t(up[0],up[1],up[2],1);
	worldCamera.setViewTransform(from_t,to_t,up_t);
	//Set light
	sceneWorld.sourceLight= light(tuple(-10,10.0,-10,1.0),tuple(1,1,1,1));
	sceneWorld.createWorldList(objects);
	//TODO create a general way of creating the scene for testing
	plane floor= plane(tuple(0,0,0,0));
	floor.shapeTransform=translation(tuple(0,0,0,1));
	//floor.set_material(tuple(0,1,0,1),0.5,0.7,0.3,400.0,0,0,0);
	floor.set_material(tuple(0,1,0,1),0.01,0.01,1,400.0,0,0.9,1.1);

	plane leftWall=plane(tuple(0,0,0,0));
	leftWall.shapeTransform=translation(tuple(0,0,5,1))*
							 rotatex(M_PI/2);
	leftWall.set_material(tuple(1,0,0,1),0.5,0.7,0.3,400.0,0,0,0);

	plane rightWall= plane(tuple(0,0,0,0));
	rightWall.shapeTransform=translation(tuple(5,0,0,1))*
							 rotatez(M_PI/2);
	rightWall.set_material(tuple(0,0,1,1),0.5,0.7,0.3,400.0,0,0,0);

	sphere middle= sphere(tuple(0,0,0,0),1);
	middle.shapeTransform=translation(tuple(0,1,0.5,1));
	middle.set_material(tuple(0.1,1,0.5,1),0.1,0.7,0.3,300.0,0.0,0,0);

	sphere right= sphere(tuple(0,0,0,0),1);
	right.shapeTransform=translation(tuple(2.5,1,0.5,1));
	/*right.shapeTransform=translation(tuple(1.5,0.5,-0.5,1))*
						   scale(tuple(0.5,0.5,0.5,1));*/
	right.set_material(tuple(0.5,1,0.1,1),0.1,0.7,0.3,200.0,0.0,0,0);

	//sphere left= sphere(tuple(0,0,0,0),1);
	/*left.shapeTransform=translation(tuple(-2.5,0.33,0.5,1))*
	scale(tuple(0.33,0.33,0.33,1));*/
	/*left.shapeTransform=translation(tuple(-1.5,1.5,0.75,1))*
						   scale(tuple(0.33,1,0.33,1));
	left.set_material(tuple(1,0.8,0.1,1),0.2,0.7,0.3,400.0,0.0,0,0);*/

	plane left= plane(tuple(0,0,0,0));
	/*left.shapeTransform=translation(tuple(-2.5,0.33,0.5,1))*
	scale(tuple(0.33,0.33,0.33,1));*/
	left.shapeTransform=translation(tuple(-1.5,0,0.75,1))*
							rotatex(-M_PI/2)*
						   scale(tuple(0.33,1,0.33,1));
	left.set_material(tuple(1,0.8,0.1,1),0.2,0.7,0.3,400.0,0.0,0,0);
	//sphere S2(tuple(0,0,0,0),0.5);
	
	/*	
		Material properties
		color=c;
		ambient=a;
		diffuse=d;
		specular=sp;
		shininess=sh;
	*/
	///S2.set_material(tuple(1,0.2,1,1),0.1,0.9,0.9,200.0);
	//sceneWorld.addObject(&floor);
	//sceneWorld.addObject(&leftWall,0);
	//sceneWorld.addObject(&rightWall,1);
	middle.shapeTransform.invertMatrix();
	left.shapeTransform.invertMatrix();
	right.shapeTransform.invertMatrix();
	middle.shapeTransform.InverseTranspose();
	left.shapeTransform.InverseTranspose();
	right.shapeTransform.InverseTranspose();


	sceneWorld.addObject(&middle,0);
	sceneWorld.addObject(&left,1);

	sceneWorld.addObject(&right,2);

	//sceneWorld.addObject(S2);
	//END TODO
	renderWorld();
}
int main(int argc, char *argv[]){
	//set coordinates and dimensions of the canvas
	//std::cout << "There are " << argc << " arguments:\n";

    // Loop through each argument and print its number and value
    for (int count{ 0 }; count < argc; ++count)
    {
        if(argv[count] == std::string("w")){
              std::stringstream temp(argv[count+1]); 
              temp >> width; 
              //std::cout <<  width<< " ancho\n";  
        }
        if(argv[count]==std::string("h")){
              std::stringstream temp(argv[count+1]); 
              temp >> height; 
              //std::cout <<  height<<" alto\n"; 
 
        }
        if(argv[count]==std::string("fv")){
              std::stringstream temp(argv[count+1]); 
              temp >> fieldview; 
              //std::cout << fieldview<< " field view\n";    
        }
        if(argv[count]==std::string("sh")){
              shadows= (std::string(argv[count+1])=="1");
              //std::cout <<  shadows << " shadows\n";    
        }
        if(argv[count]==std::string("rl")){
              reflections= (std::string(argv[count+1])=="1");
              //std::cout <<  reflections<<" reflection\n";    
        }
        if(argv[count]==std::string("rf")){
              refractions= (std::string(argv[count+1])=="1");
              //std::cout <<  refractions<<" refraction\n";    
        }
        if(argv[count]==std::string("pr")){
              precision= (std::string(argv[count+1])=="1");
              //std::cout <<  precision<<" precision\n";    
        }
        if(argv[count]==std::string("v")){
              vector= (std::string(argv[count+1])=="1");
              //std::cout <<  vector <<" vector\n";    
        }
        if(argv[count]==std::string("o")){
              std::stringstream temp(argv[count+1]); 
              temp >> objects; 
              //std::cout <<  objects<<" objects\n";    
        }
        if(argv[count]==std::string("fm")){
              std::stringstream temp(argv[count+1]); 
              temp >> from[0]; 
              std::stringstream temp1(argv[count+2]); 
              temp1 >> from[1]; 
              std::stringstream temp2(argv[count+3]); 
              temp2 >> from[2]; 
              //std::cout <<  from[0]<< " "<<from[1]<< " "<<from[2] <<" from\n";    
        }
        if(argv[count]==std::string("to")){
              std::stringstream temp(argv[count+1]); 
              temp >> to[0]; 
              std::stringstream temp1(argv[count+2]); 
              temp1 >> to[1]; 
              std::stringstream temp2(argv[count+3]); 
              temp2 >> to[2]; 
              //std::cout <<  to[0]<< " "<<to[1]<< " "<<to[2] <<" to\n";    
        }
        if(argv[count]==std::string("up")){
              std::stringstream temp(argv[count+1]); 
              temp >> up[0]; 
              std::stringstream temp1(argv[count+2]); 
              temp1 >> up[1]; 
              std::stringstream temp2(argv[count+3]); 
              temp2 >> up[2]; 
              //std::cout <<  up[0]<< " "<<up[1]<< " "<<up[2] <<" up\n";    
        }
    }
    startWorld();
    return 0;

}