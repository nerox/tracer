#ifndef TUPLE
#define TUPLE
#include <math.h>
#include <stdlib.h>
#include <iostream>
class tuple {
public:
	tuple(){
		e[0]=0;
		e[1]=0;
		e[2]=0;
		e[3]=0; //1.0 point and 0.0 vector
	}
	tuple(float e0, float e1, float e2,float e3){
		e[0]=e0;
		e[1]=e1;
		e[2]=e2;
		e[3]=e3; //1.0 point and 0.0 vector
	}
	inline float x() const { return e[0];}
	inline float y() const { return e[1];}
	inline float z() const { return e[2];}
	inline float w() const { return e[3];}
	inline float r() const { return e[0];}
	inline float g() const { return e[1];}
	inline float b() const { return e[2];}
	inline const tuple& operator+() const{ return *this;}
	inline float operator[](int i) const { return e[i];}
	inline float& operator[](int& i) { return e[i];}
	inline tuple& operator+=(const tuple &v2);
	inline tuple& operator-=(const tuple &v2);
	inline tuple& operator*=(const tuple &v2);
	inline tuple& operator/=(const tuple &v2);
	inline tuple& operator*=(const float& t);
	inline tuple& operator/=(const float& t);
	inline float length() const{
		return sqrt(e[0]*e[0]+e[1]*e[1]+e[2]*e[2]);
	}
	inline float squared_length() const{
		return e[0]*e[0]+e[1]*e[1]+e[2]*e[2];
	}
	inline void make_unit();
	float e[4];
};
inline tuple operator+(const tuple &v1, const tuple &v2){
	//type is kept from the first input
	return tuple(v1.e[0]+v2.e[0],v1.e[1]+v2.e[1],v1.e[2]+v2.e[2],v1.e[3]);
}
inline tuple operator-(const tuple &v1, const tuple &v2){
	 return tuple(v1.e[0]-v2.e[0],v1.e[1]-v2.e[1],v1.e[2]-v2.e[2],v1.e[3]-v2.e[3]);
}
inline tuple operator*(const tuple &v1, const tuple &v2){
	//type is kept from the first input
	 return tuple(v1.e[0]*v2.e[0],v1.e[1]*v2.e[1],v1.e[2]*v2.e[2],v1.e[3]);
}
inline tuple operator/(const tuple &v1, const tuple &v2){
	//type is kept from the first input
	 return tuple(v1.e[0]/v2.e[0],v1.e[1]/v2.e[1],v1.e[2]/v2.e[2],v1.e[3]);
}
inline tuple operator*(float& t, const tuple &v){
	//type is kept from the first input
	 return tuple(t*v.e[0],t*v.e[1],t*v.e[2],v.e[3]);
}
inline tuple operator*(const tuple &v, float t){
	//type is kept from the first input
	 return tuple(t*v.e[0],t*v.e[1],t*v.e[2],v.e[3]);
}
inline tuple operator/(float t, const tuple v){
	//type is kept from the first input
	 return tuple(t/v.e[0],t/v.e[1],t/v.e[2],v.e[3]);
}
inline tuple operator/(const tuple v,float t){
	//type is kept from the first input
	 return tuple(v.e[0]/t,v.e[1]/t,v.e[2]/t,v.e[3]);
}
inline tuple operator+(float& t, const tuple &v){
	//type is kept from the first input
	 return tuple(t+v.e[0],t+v.e[1],t+v.e[2],v.e[3]);
}
inline tuple operator-(float& t, const tuple &v){
	//type is kept from the first input
	 return tuple(t-v.e[0],t-v.e[1],t-v.e[2],v.e[3]);
}
inline float dot(const tuple &v1, const tuple &v2){
	return v1.e[0]*v2.e[0]+v1.e[1]*v2.e[1]+v1.e[2]*v2.e[2];
}
inline tuple cross(const tuple &v1, const tuple &v2){
	return tuple ((v1.e[1]*v2.e[2]-v1.e[2]*v2.e[1]),
				 (-(v1.e[0]*v2.e[2]-v1.e[2]*v2.e[0])),
				 (v1.e[0]*v2.e[1]-v1.e[1]*v2.e[0]),
				 (v1.e[3])
				 );
}
inline tuple negate_tuple(tuple& t){

	return tuple(-t.e[0],-t.e[1],-t.e[2],t[3]);

}
inline tuple unit_vector(tuple t){
	return t/t.length();
}
#endif