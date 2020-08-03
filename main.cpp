#include <iostream>
#include "shape.h"
#include "tuple.h"
#include "ray.h"
#include "sphere.h"
#include "plane.h"
#include "light.h"
#include "world.h"
#include "hitList.h"
#include "matrix.h"
#include "camera.h"
#define EPSILON 0.0001
#define REMAIN 2
world sceneWorld;
tuple color(const ray& r, int remain,std::list<shape*> *containers);
tuple lighting(const material& input_material, const light& input_light, const tuple& point,
				const tuple& eyev, const tuple& normalv, const bool isShadow, const double transparency){
	tuple effective_color= input_material.color*input_light.intensity;
	tuple lightv= unit_vector(input_light.position-point);
	tuple ambient= effective_color*input_material.ambient;
	double light_dot_normal= dot(lightv,normalv);
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
		double reflect_dot_eye= dot(reflectv,eyev);
		if (reflect_dot_eye<=0){
		 	specular=tuple(0,0,0,1);
		}
		else{
		 	double factor= pow (reflect_dot_eye,input_material.shininess);
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
ray rayforPixel(const camera& inputCam, int px, int py){
	double xoffset = (px+0.5)*inputCam.pixelSize;
	double yoffset = (py+0.5)*inputCam.pixelSize;
	double worldx = inputCam.halfWidth - xoffset;
	double worldy = inputCam.halfHeight - yoffset;
	matrix invCamera= invertMatrix(inputCam.cameraTransform);
	tuple pixel=  tuple(worldx,worldy,-1,1)*invCamera;
	tuple origin = tuple(0,0,0,1)*invCamera;
	//normalize 
	tuple direction = unit_vector(pixel-origin);
	return ray(origin,direction);
}
tuple reflectedworld(double objectReflectance, tuple reflectv,tuple overPoint, int remain,std::list<shape*> *containers){

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
void setRefractiveIndexes(std::list<shape*> *containers, double* n1, double* n2,  shape* objectShape){
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
tuple refractedworld(tuple underPoint, tuple normalv, tuple eyev,
					 double transparency, double nratio,
					 double sin2_t, double cos_i,int remain, std::list<shape*> *containers){
	if(transparency==0 || remain<=0){
		return tuple(0,0,0,1);
	}
	else{
		double cos_t = sqrt(1.0-sin2_t);
		tuple direction= normalv*(nratio*cos_i-cos_t)-eyev*nratio;
		ray refactRay(underPoint,direction);
		return color(refactRay,remain-1,containers)*transparency;
	}
}
bool isPointShadow(const tuple inputPoint, const int remain){
	tuple v = sceneWorld.sourceLight.position-inputPoint;
	double distance = v.length();
	tuple direction = unit_vector(v);
	ray r(inputPoint,direction);
	hitList pointHitList;
	std::list<shape*>::iterator it;
	//TODO REMOVE REPLICATED CODE
	for (it = sceneWorld.objectsInWorld.begin(); it != sceneWorld.objectsInWorld.end(); ++it){
		std::list<double> result_hit=(*it)->ray_hits_me(r);
		std::list<double>::iterator localit;
		for (localit = result_hit.begin(); localit != result_hit.end(); ++localit){
			pointHitList.addHit( *localit,(*it)->shapeMaterial,*it);
		} 
	}
	if(pointHitList.gethitListSize()>0){
		pointHitList.hitListSort();
		double nearHitPoint= pointHitList.localHitList.begin()->hitPoint;
		material nearHitPointMaterial= pointHitList.localHitList.begin()->hitObjectMaterial;
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
	std::list<shape*>::iterator it;
	hitList pointHitList;

	for (it = sceneWorld.objectsInWorld.begin(); it != sceneWorld.objectsInWorld.end(); ++it){
		std::list<double> result_hit=(*it)->ray_hits_me(r);
		std::list<double>::iterator localit;
		for (localit = result_hit.begin(); localit != result_hit.end(); ++localit){
			pointHitList.addHit( *localit,(*it)->shapeMaterial,*it);
		} 
	}
	if(pointHitList.gethitListSize()>0){
		/*Start  Comps 3046*/
		pointHitList.hitListSort();
		double nearHitPoint= pointHitList.localHitList.begin()->hitPoint;
		material nearHitPointMaterial= pointHitList.localHitList.begin()->hitObjectMaterial;
		shape* objectShape = pointHitList.localHitList.begin()->shapeAdress;
		tuple rdir=r.direction();
		tuple position=r.point_at_parameter(nearHitPoint);
		//Define surface normal
		tuple normalv=objectShape->normal_at(position);
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
		double n1;
		double n2;
		setRefractiveIndexes(containers, &n1, &n2, objectShape);
		double nratio=n1/n2;
		double cos_i=dot(eyev,normalv);
		double sin2_t=pow(nratio,2)*(1-pow(cos_i,2));
		/*End Comps*/
		/*Shade Hit function*/
		bool isShadow=isPointShadow(over_point,5);
		tuple color= lighting(nearHitPointMaterial, sceneWorld.sourceLight,over_point,eyev, normalv,isShadow,nearHitPointMaterial.transparency);
		/*std::cout << color.x() << " " << color.y() << " " << color.z() << " color \n";
		std::cout << reflectv.x() << " " << reflectv.y() << " " << reflectv.z() << " reflectv \n";
		std::cout << over_point.x() << " " << over_point.y() << " " << over_point.z() << " over_point \n";*/

		tuple refractedColor=refractedworld(under_point, normalv,eyev,nearHitPointMaterial.transparency,
											nratio,sin2_t,cos_i, remain,containers);
		tuple reflectedColor=reflectedworld( nearHitPointMaterial.reflective, reflectv, over_point,remain, containers);
		return color+refractedColor+reflectedColor;

	}
	return tuple(0.0,0.0,0.0,1.0);
}
void renderWorld(const camera& worldCamera){
	int j,i;
	//worldCamera.vsize
	//worldCamera.hsize
	for (j=0;j<worldCamera.vsize;j++){
		for(i=0;i <worldCamera.hsize;i++){
			ray r= rayforPixel(worldCamera, i, j);
			std::list<shape*> containers;
			tuple col = color(r,REMAIN, &containers);
			int ir = int(255.99*col.r()); 
			int ig = int(255.99*col.g()); 
			int ib = int(255.99*col.b()); 
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}
void ray_at_pixel(const camera& worldCamera,int i,int j){
	ray r= rayforPixel(worldCamera, i, j);
	std::cout << r.origin().x() << " " << r.origin().y()<< " " << r.origin().z() << "\n";
	std::cout << r.direction().x() << " " << r.direction().y()<< " " << r.direction().z() << "\n";
	std::list<shape*> containers;
	tuple col = color(r,2,&containers);
	int ir = int(255.99*col.r()); 
	int ig = int(255.99*col.g()); 
	int ib = int(255.99*col.b()); 
	//std::cout << col.r() << " " << col.g() << " " << col.b() << "\n";

}
int main(){
	double canvasPixelsx=1920;
	double canvasPixelsy=1080;
	//set coordinates and dimensions of the canvas
	std::cout << "P3\n" << canvasPixelsx << " "<< canvasPixelsy << "\n255\n";
	//CREATE camera
	// with fieldview of pi/2
	camera worldCamera(canvasPixelsx,canvasPixelsy,M_PI/2);
	tuple from(0,3,-5,1);
	tuple to (0,0,0,1);
	tuple up(0,5,0,1);
	worldCamera.setViewTransform(from,to,up);
	//Set light
	sceneWorld.sourceLight= light(tuple(-10,10.0,-10,1.0),tuple(1,1,1,1));

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

	sphere left= sphere(tuple(0,0,0,0),1);
	/*left.shapeTransform=translation(tuple(-2.5,0.33,0.5,1))*
	scale(tuple(0.33,0.33,0.33,1));*/
	left.shapeTransform=translation(tuple(-1.5,1.5,0.75,1))*
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
	sceneWorld.addObject(&floor);
	sceneWorld.addObject(&leftWall);
	sceneWorld.addObject(&rightWall);
	//sceneWorld.addObject(&middle);
	sceneWorld.addObject(&left);
	//sceneWorld.addObject(&right);

	//sceneWorld.addObject(S2);
	//END TODO

	renderWorld(worldCamera);
}