#ifndef RAYH
#define RAYH
#include "tuple.h"

class ray
{
	public:
	ray(){}
	ray(const tuple& a, const tuple& b){A=a;B=b;}
	tuple origin() const { return A;}
	tuple direction() const { return B;}
	tuple point_at_parameter(double t )const {return A+t*B;}
	tuple A;
	tuple B;

};
#endif