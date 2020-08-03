#ifndef SHAPE
#define SHAPE
#include "tuple.h"
#include "matrix.h"
#include "material.h"
#include "ray.h"
#include <iostream>
#include <list>

class shape
{
  public:
  	void set_material(const tuple& c, double a,double d, 
  							 double sp,double sh, double rf,
  							 double tr,double ri);
    virtual tuple normal_at(tuple point){
    	return tuple(0,1,0,1);
    }
	virtual std::list<double> ray_hits_me(const ray& r){
		std::list<double> localHitList;
		return localHitList;
	}
	tuple center;
	matrix shapeTransform;
	material shapeMaterial;
};
void shape::set_material(const tuple& c, double a,double d, double sp,double sh, double rf,double tr,double ri){
	this->shapeMaterial= material(c,a,d,sp,sh,rf,tr,ri);
}
#endif
