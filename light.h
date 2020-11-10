#ifndef LIGHT
#define LIGHT
#include <math.h>
#include "tuple.h"
#include "material.h"
class light
{
	public:
	light(){}
	light(const tuple p, tuple i){position=p;intensity=i;}
	tuple position;
	tuple intensity;
};
tuple reflect(const tuple& in,const tuple& normal){
	return in-(normal*2*dot(in,normal));
}

#endif