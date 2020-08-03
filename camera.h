#ifndef CAMERA
#define CAMERA
#include <math.h>
#include "tuple.h"
class camera {
public:
	camera(double hs, double vs, double fv){
		hsize=hs;
		vsize=vs;
		fieldOfView=fv;
		cameraTransform.setIdentity();
		halfView=tan(fieldOfView/2.0);
		aspect=hsize/vsize;
		if (aspect>=1){
			halfWidth=halfView;
			halfHeight=halfView/aspect;
		}
		else{
			halfWidth=halfView*aspect;
			halfHeight=halfView;

		}
		pixelSize=(halfWidth*2.0)/hsize;
	}
	void setViewTransform(tuple& from, const tuple& to, const tuple& up);
	double hsize;
	double vsize;
	double fieldOfView;
	double pixelSize;
	double halfView;
	double aspect;
	double halfWidth;
	double halfHeight;
	matrix  cameraTransform;
};
void camera::setViewTransform( tuple& from, const tuple& to, const tuple& up){
	tuple forward =unit_vector(to-from);
	tuple upn = unit_vector(up);
	tuple left = cross(forward,upn);
	tuple trueup= cross(left,forward);
	forward= negate_tuple(forward);
	from= negate_tuple(from);
	matrix orientation= matrix(left.x(),left.y(),left.z(),0,
						trueup.x(),trueup.y(),trueup.z(),0,
						forward.x(),forward.y(),forward.z(),0,
						0,0,0,1);
	this->cameraTransform= orientation*translation(from);
}
#endif 