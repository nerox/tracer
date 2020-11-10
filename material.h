#ifndef MATERIAL
#define MATERIAL
#include "tuple.h"

class material
{
	public:
	material(){}
	material(const tuple& c, double& a,
			double& d, double& sp,
			double& sh,double& rf,
			double& tr, double& ri){
		color=c;
		ambient=a;
		diffuse=d;
		specular=sp;
		shininess=sh;
		reflective=rf;
		transparency=tr;
		refractionIndex=ri;

	}
	tuple color;
	double ambient;
	double diffuse;
	double specular;
	double shininess;
	double reflective;
	double transparency;
	double refractionIndex;

};
#endif