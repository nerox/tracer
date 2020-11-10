#include <math.h>
#include <stdio.h>      /* printf, fopen */
#include <stdlib.h>
#include <iostream>
#include "tuple.h"

inline std::istream& operator>>(std::istream &is, tuple &t){
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
}

inline std::ostream& operator<<(std::ostream &os, const tuple &t){
	os << t.e[0] << " " << t.e[1] << " " << t.e[2];
	return os;
}
inline void tuple::make_unit(){
	float k= 1.0/ sqrt(e[0]*e[0]+e[1]*e[1]+e[2]*e[2]);
	e[0] *= k; 
	e[1] *= k; 
	e[2] *= k;
}
inline tuple& tuple::operator+=(const tuple &v){
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];
	return *this;
}
inline tuple& tuple::operator*=(const tuple &v){
	e[0] *= v.e[0];
	e[1] *= v.e[1];
	e[2] *= v.e[2];
	return *this;
}
inline tuple& tuple::operator/=(const tuple &v){
	e[0] /= v.e[0];
	e[1] /= v.e[1];
	e[2] /= v.e[2];
	return *this;
}
inline tuple& tuple::operator-=(const tuple &v){
	e[0] -= v.e[0];
	e[1] -= v.e[1];
	e[2] -= v.e[2];
	return *this;	
}
inline tuple& tuple::operator*=(const float& t){
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;	
}
inline tuple& tuple::operator/=(const float& t){
	float k= 1.0/t;
	e[0] *= k;
	e[1] *= k;
	e[2] *= k;
	return *this;	
}