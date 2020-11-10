#ifndef CUBE
#define CUBE
#include "tuple.h"
#include "material.h"
#include "matrix.h"
#include "shape.h"
#include <algorithm>    // std::swap
#include <stdlib.h>     /* abs */
#include <limits>
#include <iostream>
#include <list>
class cube: public shape
{
	public:
	cube(const tuple& c)
	{
		center=c;
		shapeTransform.setIdentity();
	}
	float ray_hits_me(const ray& r, float& near_hit_point){
		matrix inv=invertMatrix(this->shapeTransform);
		tuple transformRayOrigin=r.origin()*inv;
		tuple transformRayDestination=r.direction()*inv;
		float tmin,tmax;
		float xt[2]; 
		float yt[2]; 
		float zt[2]; 

		check_axis(transformRayOrigin.x(),transformRayDestination.x(),xt);
		check_axis(transformRayOrigin.y(),transformRayDestination.y(),yt);
		check_axis(transformRayOrigin.z(),transformRayDestination.z(),zt);
		tmin=maximum(xt[0],yt[0],zt[0]);
		tmax=minimum(xt[1],yt[1],zt[1]);
		if (tmin< tmax && tmin>0 && tmax>0)
		{
			
			near_hit_point=tmin;
		}

		return near_hit_point;
	};
	float maximum( float a, float b, float c )
	{
		float max = ( a < b ) ? b : a;
		return ( ( max < c ) ? c : max );
	}
	float minimum( float a, float b, float c )
	{
		float max = ( a > b ) ? b : a;
		return ( ( max > c ) ? c : max );
	}
	tuple normal_at(tuple& point){
		matrix inv = invertMatrix(this->shapeTransform);
		tuple object_point=point*inv;
		float maxc=maximum(abs(object_point.x()),abs(object_point.y()),abs(object_point.z()));
		tuple object_normal;
		if (maxc==abs(object_point.x())){
			object_normal=tuple(1,0,0,0);
		} 
		else if(maxc==abs(object_point.y())){
			object_normal=tuple(0,1,0,0);
		}
		else{
			object_normal=tuple(0,0,1,0);
		}
		inv.transpose();
		object_normal.e[3]=0;
		tuple world_normal=object_normal*inv;

		tuple u=unit_vector(world_normal);
		//std::cout << u.x() << " " << u.y() << " " << u.z() << " world_normal \n";
		return u;
	};
	void check_axis(const float& origin,const float& direction, float ts[]){
		float tmin_numerator=(-1 - origin);
		float tmax_numerator=( 1 - origin);
		float tmin,tmax;
		if (abs(direction)>= EPSILON2){
			tmin= tmin_numerator/direction;
			tmax= tmax_numerator/direction;
		}
		else{
			tmin= tmin_numerator*std::numeric_limits<float>::infinity();
			tmax= tmax_numerator*std::numeric_limits<float>::infinity();			
		}
		if(tmin>tmax){
			std::swap(tmin,tmax);
		}
		ts[0]=tmin;
		ts[1]=tmax;
	}

};

#endif
