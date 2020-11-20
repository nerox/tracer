#ifndef CYLINDER
#define CYLINDER
#include "tuple.h"
#include "material.h"
#include "matrix.h"
#include "shape.h"
#include <algorithm>    // std::swap
#include <stdlib.h>     /* abs */
#include <limits>
#include <iostream>
#include <list>
class cylinder: public shape
{
	public:
	cylinder(const tuple& c, const bool& cl)
	{
		center=c;
		shapeTransform.setIdentity();
		minimum=-1*std::numeric_limits<float>::infinity();
		maximum=std::numeric_limits<float>::infinity();
		closed=cl;
	}
	cylinder(const tuple& c, const float& min, const float& max, const bool& cl)
	{
		center=c;
		shapeTransform.setIdentity();
		minimum=min;
		maximum=max;
		closed=cl;
	}
	float ray_hits_me(const ray& r, float near_hit_point){
		tuple transformRayOrigin=this->shapeTransform.mutiplyinverse(r.origin());
		tuple transformRayDestination=this->shapeTransform.mutiplyinverse(r.direction());
		float a= pow(transformRayDestination.x(),2)+pow(transformRayDestination.z(),2);
		if (abs(a)<=EPSILON2){ 
			return intersect_caps(transformRayOrigin,transformRayDestination,near_hit_point);
		}
		float b= 2*transformRayOrigin.x()*transformRayDestination.x()+
				  2*transformRayOrigin.z()*transformRayDestination.z();
		float c= pow(transformRayOrigin.x(),2)+pow(transformRayOrigin.z(),2)-1;
		float disc= pow(b,2)-4*a*c;
		if (disc<EPSILON2){
			return near_hit_point;
		}
		float t0= (-b-sqrt(disc))/(2*a);
		float t1= (-b+sqrt(disc))/(2*a);
		if(t0>t1){
			std::swap(t0,t1);
		}
		float y0= transformRayOrigin.y()+t0*transformRayDestination.y();
		if(minimum<y0 && y0<maximum && t0>=EPSILON2 && near_hit_point>t0){
			near_hit_point=t0;
		}
		float y1= transformRayOrigin.y()+t1*transformRayDestination.y();
		if(minimum<y1 && y1<maximum && t1>=EPSILON2 && near_hit_point>t1){
			near_hit_point=t1;
		}
		return intersect_caps(transformRayOrigin,transformRayDestination,near_hit_point);
	};
	tuple normal_at(tuple& point){
		tuple object_point=this->shapeTransform.mutiplyinverse(point); 
		float dist= (pow(object_point.x(),2)+pow(object_point.z(),2));
		tuple object_normal;
		if(dist<1 and object_point.y()>=maximum-EPSILON2){
			object_normal=tuple(0,1,0,0);		}
		else if(dist<1 and object_point.y()<=minimum+EPSILON2){
			object_normal=tuple(0,-1,0,0);	
		}
		else{
			object_normal=tuple(object_point.x(),0,object_point.z(),0);
		}
		object_normal.e[3]=0;
		tuple world_normal=this->shapeTransform.mutiplyinverseTanspose(object_normal);

		tuple u=unit_vector(world_normal);
		//std::cout << u.x() << " " << u.y() << " " << u.z() << " world_normal \n";
		return u;
	};
	bool check_cap(const tuple& origin, const tuple& direction, float& t){
		float x = origin.x()+t*direction.x();
		float z = origin.z()+t*direction.z();
		return (pow(x,2)+pow(z,2))<= 1;
	}
	float intersect_caps(const tuple& origin, const tuple& direction,float& near_hit_point){
		if(closed==false || abs(direction.y())<EPSILON2){
			return near_hit_point;
		}
		float t0=(minimum-origin.y())/direction.y();
		if(check_cap(origin,direction,t0) && t0>=EPSILON2 && near_hit_point> t0){
			near_hit_point=t0;
		}
		float t1=(maximum-origin.y())/direction.y();
		if(check_cap(origin,direction,t1) && t1>=EPSILON2 && near_hit_point> t1){
			near_hit_point=t1;
		}
		return near_hit_point;		
	}
	float minimum;
	float maximum;
	bool closed;
};

#endif
