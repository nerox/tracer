#ifndef SHAPE
#define SHAPE
#include "tuple.h"
#include "matrix.h"
#include "material.h"
#include "ray.h"
#include <iostream>
#include <list>
#define EPSILON2 0.0001

class shape
{
  public:
  	void set_material(const tuple& c, float a,float d, 
  							 float sp,float sh, float rf,
  							 float tr,float ri);
    virtual tuple normal_at(tuple & point){
    	return tuple(0,1,0,1);
    }
	virtual float ray_hits_me(const ray& r, float near_hit_point){
		return near_hit_point;
	}
	tuple center;
	matrix shapeTransform;
	material shapeMaterial;
};
void shape::set_material(const tuple& c, float a,float d, float sp,float sh, float rf,float tr,float ri){
	this->shapeMaterial= material(c,a,d,sp,sh,rf,tr,ri);
}
#endif
