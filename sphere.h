#ifndef SPHERE
#define SPHERE
#include "tuple.h"
#include "material.h"
#include "matrix.h"
#include "shape.h"
#include <iostream>
#include <list>
class sphere: public shape
{
	public:
	sphere(const tuple& c, float r){center=c;
									radius=r;
									shapeTransform.setIdentity();
									}
	float ray_hits_me(const ray& r, float near_hit_point){
		tuple transformRayOrigin=this->shapeTransform.mutiplyinverse(r.origin());
		tuple transformRayDestination=this->shapeTransform.mutiplyinverse(r.direction());
		tuple oc= transformRayOrigin-this->center;
		float a = dot(transformRayDestination, transformRayDestination);
		float b = 2.0*dot(oc,transformRayDestination);
		float c = dot(oc,oc)-1;//this->radius*this->radius;
		float discriminant = b*b - 4.0*a*c;
		float t1=(-b-sqrt(discriminant))/(2*a);
		float t2=(-b+sqrt(discriminant))/(2*a);
		//std::cout << t1 << "esfera \n";
		//std::cout << t2 << "esfera \n";
		if(discriminant >0){
				if(t1>=0 && near_hit_point>t1){
					near_hit_point=t1;
				}
				if(t2>=0 && near_hit_point>t2){
					near_hit_point=t2;
				}
			}
		return near_hit_point;
	};
	tuple normal_at(tuple& point){
		tuple object_point=this->shapeTransform.mutiplyinverse(point); 
		tuple object_normal=object_point-tuple(0,0,0,0);
		//inv.transpose();
		object_normal.e[3]=0;
		tuple world_normal=this->shapeTransform.mutiplyinverseTanspose(object_normal);

		tuple u=unit_vector(world_normal);
		//std::cout << u.x() << " " << u.y() << " " << u.z() << " world_normal \n";
		return u;
	};
	float radius;
};

#endif
