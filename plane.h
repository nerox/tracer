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
	std::list<double> ray_hits_me(const ray& r){
		std::list<double> localHitList;
		matrix inv=invertMatrix(this->shapeTransform);
		tuple transformRayOrigin=r.origin()*inv;
		tuple transformRayDestination=r.direction()*inv;
		//std::cout << transformRayDestination.y() << "\n";
		if(abs(transformRayDestination.y())>EPSILON2){
			double t=-transformRayOrigin.y()/transformRayDestination.y();
			if(t>=0){
				localHitList.push_back(t);
			}
		}
		return localHitList;
	}
	tuple normal_at(tuple point){
		matrix inv = invertMatrix(this->shapeTransform);
		tuple object_normal=tuple(0,1,0,1);
		inv.transpose();
		object_normal.e[3]=0;

		tuple world_normal=object_normal*inv;
		//world_normal.e[3]=0;
		return unit_vector(world_normal);
	};
};
#endif
