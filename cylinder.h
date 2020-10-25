#ifndef CYLINDER
#define CYLINDER
#include "tuple.h"
#include "material.h"
#include "matrix.h"
#include "shape.h"
#include <algorithm>    // std::swap
#include <stdlib.h>     /* abs */
#include <limits>
#include <iostream>
#include <list>
class cylinder: public shape
{
	public:
	cylinder(const tuple& c, const bool cl)
	{
		center=c;
		shapeTransform.setIdentity();
		minimum=-1*std::numeric_limits<double>::infinity();
		maximum=std::numeric_limits<double>::infinity();
		closed=cl;
	}
	cylinder(const tuple& c, const double min, const double max, const bool cl)
	{
		center=c;
		shapeTransform.setIdentity();
		minimum=min;
		maximum=max;
		closed=cl;
	}
	double ray_hits_me(const ray& r, double near_hit_point){
		matrix inv=invertMatrix(this->shapeTransform);
		tuple transformRayOrigin=r.origin()*inv;
		tuple transformRayDestination=r.direction()*inv;
		double a= pow(transformRayDestination.x(),2)+pow(transformRayDestination.z(),2);
		if (abs(a)<=0){ 
			return intersect_caps(transformRayOrigin,transformRayDestination,near_hit_point);
		}
		double b= 2*transformRayOrigin.x()*transformRayDestination.x()+
				  2*transformRayOrigin.z()*transformRayDestination.z();
		double c= pow(transformRayOrigin.x(),2)+pow(transformRayOrigin.z(),2)-1;
		double disc= pow(b,2)-4*a*c;
		if (disc<0){
			return near_hit_point;
		}
		double t0= (-b-sqrt(disc))/(2*a);
		double t1= (-b+sqrt(disc))/(2*a);
		if(t0>t1){
			std::swap(t0,t1);
		}
		double y0= transformRayOrigin.y()+t0*transformRayDestination.y();
		if(minimum<y0 && y0<maximum && t0>=0 && near_hit_point>t0){
			near_hit_point=t0;
		}
		double y1= transformRayOrigin.y()+t1*transformRayDestination.y();
		if(minimum<y1 && y1<maximum && t1>=0 && near_hit_point>t1){
			near_hit_point=t1;
		}
		return intersect_caps(transformRayOrigin,transformRayDestination,near_hit_point);
	};
	tuple normal_at(tuple point){
		matrix inv = invertMatrix(this->shapeTransform);
		tuple object_point=point*inv;
		double dist= (pow(object_point.x(),2)+pow(object_point.z(),2));
		tuple object_normal;
		if(dist<1 and object_point.y()>=maximum-EPSILON2){
			object_normal=tuple(0,1,0,0);		}
		else if(dist<1 and object_point.y()<=minimum+EPSILON2){
			object_normal=tuple(0,-1,0,0);	
		}
		else{
			object_normal=tuple(object_point.x(),0,object_point.z(),0);
		}
		inv.transpose();
		tuple world_normal=object_normal*inv;

		tuple u=unit_vector(world_normal);
		//std::cout << u.x() << " " << u.y() << " " << u.z() << " world_normal \n";
		return u;
	};
	bool check_cap(const tuple& origin, const tuple& direction, double t){
		double x = origin.x()+t*direction.x();
		double z = origin.z()+t*direction.z();
		return (pow(x,2)+pow(z,2))<= 1;
	}
	double intersect_caps(const tuple& origin, const tuple& direction,double near_hit_point){
		if(closed==false || abs(direction.y())<EPSILON2){
			return near_hit_point;
		}
		double t0=(minimum-origin.y())/direction.y();
		if(check_cap(origin,direction,t0) && t0>=0 && near_hit_point> t0){
			near_hit_point=t0;
		}
		double t1=(maximum-origin.y())/direction.y();
		if(check_cap(origin,direction,t1) && t1>=0 && near_hit_point> t1){
			near_hit_point=t1;
		}
		return near_hit_point;		
	}
	double minimum;
	double maximum;
	bool closed;
};

#endif
