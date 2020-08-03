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
	sphere(const tuple& c, double r){center=c;
									radius=r;
									shapeTransform.setIdentity();
									}
	std::list<double> ray_hits_me(const ray& r){
		std::list<double> localHitList;
		matrix inv=invertMatrix(this->shapeTransform);
		tuple transformRayOrigin=r.origin()*inv;
		tuple transformRayDestination=r.direction()*inv;
		tuple oc= transformRayOrigin-this->center;
		double a = dot(transformRayDestination, transformRayDestination);
		double b = 2.0*dot(oc,transformRayDestination);
		double c = dot(oc,oc)-1;//this->radius*this->radius;
		double discriminant = b*b - 4.0*a*c;
		double t1=(-b-sqrt(discriminant))/(2*a);
		double t2=(-b+sqrt(discriminant))/(2*a);
		//std::cout << t1 << "esfera \n";
		//std::cout << t2 << "esfera \n";
		if(discriminant >0){
				if(t1>=0){
					localHitList.push_back(t1);
				}
				if(t2>=0){
					localHitList.push_back(t2);
				}
			}
		return localHitList;
	};
	tuple normal_at(tuple point){
		matrix inv = invertMatrix(this->shapeTransform);
		tuple object_point=point*inv;
		tuple object_normal=object_point-tuple(0,0,0,0);
		inv.transpose();
		object_normal.e[3]=0;
		tuple world_normal=object_normal*inv;

		tuple u=unit_vector(world_normal);
		//std::cout << u.x() << " " << u.y() << " " << u.z() << " world_normal \n";
		return u;
	};
	double radius;
};

#endif
