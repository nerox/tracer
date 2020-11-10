#ifndef MATERIAL
#define MATERIAL
#include "tuple.h"

class material
{
	public:
	material(){}
	material(const tuple& c, float& a,
			float& d, float& sp,
			float& sh,float& rf,
			float& tr, float& ri){
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
	float ambient;
	float diffuse;
	float specular;
	float shininess;
	float reflective;
	float transparency;
	float refractionIndex;

};
#endif