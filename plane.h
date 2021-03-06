#ifndef PLANE
#define PLANE
#include "tuple.h"
#include "material.h"
#include "matrix.h"
#include "shape.h"
#include <iostream>
#include <stdlib.h>     /* abs */
#include <list>

class plane: public shape
{
	public:
	plane(const tuple& c){center=c;
						  shapeTransform.setIdentity();
						 }
	float ray_hits_me(const ray& r, float near_hit_point){
		tuple transformRayOrigin=this->shapeTransform.mutiplyinverse(r.origin());
		tuple transformRayDestination=this->shapeTransform.mutiplyinverse(r.direction());
		//std::cout << transformRayDestination.y() << "\n";
		if(abs(transformRayDestination.y())>EPSILON2){
			float t=-transformRayOrigin.y()/transformRayDestination.y();
			if(t>=EPSILON2 && near_hit_point>t){
				near_hit_point=t;
			}
		}
		return near_hit_point;
	}
	tuple normal_at(tuple& point){
		tuple object_point=this->shapeTransform.mutiplyinverse(point); 
		tuple object_normal=tuple(0,1,0,0);
		tuple world_normal=this->shapeTransform.mutiplyinverseTanspose(object_normal);
		//world_normal.e[3]=0;
		return unit_vector(world_normal);
	};
};
#endif
