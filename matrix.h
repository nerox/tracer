#ifndef MATRIX
#define MATRIX
#include <math.h>
#include <iostream>
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include "tuple.h"
class matrix {
public:
	float transformationMatrix [4][4];
	float inverseTransformationMatrix [4][4];

	matrix(){
	}
	matrix(float i0, float i1,float i2, float i3,
		   float i4, float i5,float i6, float i7,
		   float i8, float i9,float i10, float i11,
		   float i12, float i13,float i14, float i15){

		transformationMatrix[0][0]=i0;
		transformationMatrix[0][1]=i1;
		transformationMatrix[0][2]=i2;
		transformationMatrix[0][3]=i3;

		transformationMatrix[1][0]=i4;
		transformationMatrix[1][1]=i5;
		transformationMatrix[1][2]=i6;
		transformationMatrix[1][3]=i7;

		transformationMatrix[2][0]=i8;
		transformationMatrix[2][1]=i9;
		transformationMatrix[2][2]=i10;
		transformationMatrix[2][3]=i11;

		transformationMatrix[3][0]=i12;
		transformationMatrix[3][1]=i13;
		transformationMatrix[3][2]=i14;
		transformationMatrix[3][3]=i15;

	}
	void setIdentity(){
		transformationMatrix[0][0]=1;
		transformationMatrix[0][1]=0;
		transformationMatrix[0][2]=0;
		transformationMatrix[0][3]=0;

		transformationMatrix[1][0]=0;
		transformationMatrix[1][1]=1;
		transformationMatrix[1][2]=0;
		transformationMatrix[1][3]=0;

		transformationMatrix[2][0]=0;
		transformationMatrix[2][1]=0;
		transformationMatrix[2][2]=1;
		transformationMatrix[2][3]=0;

		transformationMatrix[3][0]=0;
		transformationMatrix[3][1]=0;
		transformationMatrix[3][2]=0;
		transformationMatrix[3][3]=1;

	}
	void transpose();
	void invertMatrix();
	tuple mutiplyinverse(const tuple& t);
};
void printmematrix(const matrix& m){
	std::cout << m.transformationMatrix[0][0]<< " "<<m.transformationMatrix[0][1]<< " "<< m.transformationMatrix[0][2]<< " "<<m.transformationMatrix[0][3]<<"\n";
	std::cout << m.transformationMatrix[1][0]<< " "<<m.transformationMatrix[1][1]<< " "<< m.transformationMatrix[1][2]<< " "<<m.transformationMatrix[1][3]<<"\n";
	std::cout << m.transformationMatrix[2][0]<< " "<<m.transformationMatrix[2][1]<< " "<< m.transformationMatrix[2][2]<< " "<<m.transformationMatrix[2][3]<<"\n";
	std::cout << m.transformationMatrix[3][0]<< " "<<m.transformationMatrix[3][1]<< " "<< m.transformationMatrix[3][2]<< " "<<m.transformationMatrix[3][3]<<"\n";

}
void matrix::transpose(){
	float transPoseMatrix [4][4];
	transPoseMatrix[0][0]=transformationMatrix[0][0];
	transPoseMatrix[0][1]=transformationMatrix[1][0];
	transPoseMatrix[0][2]=transformationMatrix[2][0];
	transPoseMatrix[0][3]=transformationMatrix[3][0];

	transPoseMatrix[1][0]=transformationMatrix[0][1];
	transPoseMatrix[1][1]=transformationMatrix[1][1];
	transPoseMatrix[1][2]=transformationMatrix[2][1];
	transPoseMatrix[1][3]=transformationMatrix[3][1];

	transPoseMatrix[2][0]=transformationMatrix[0][2];
	transPoseMatrix[2][1]=transformationMatrix[1][2];
	transPoseMatrix[2][2]=transformationMatrix[2][2];
	transPoseMatrix[2][3]=transformationMatrix[3][2];

	transPoseMatrix[3][0]=transformationMatrix[0][3];
	transPoseMatrix[3][1]=transformationMatrix[1][3];
	transPoseMatrix[3][2]=transformationMatrix[2][3];
	transPoseMatrix[3][3]=transformationMatrix[3][3];
	int j;
	for (j = 0; j < 4; j++){
		transformationMatrix[j][0]=transPoseMatrix[j][0];
		transformationMatrix[j][1]=transPoseMatrix[j][1];
		transformationMatrix[j][2]=transPoseMatrix[j][2];
		transformationMatrix[j][3]=transPoseMatrix[j][3];
    	}
	}
void matrix::invertMatrix(){
    float det;
    int i,j;
    inverseTransformationMatrix[0][0] =  transformationMatrix[1][1] * transformationMatrix[2][2] * transformationMatrix[3][3] - 
                					 transformationMatrix[1][1] * transformationMatrix[2][3] * transformationMatrix[3][2] - 
                					 transformationMatrix[2][1] * transformationMatrix[1][2] * transformationMatrix[3][3] + 
                					 transformationMatrix[2][1] * transformationMatrix[1][3] * transformationMatrix[3][2] +
                					 transformationMatrix[3][1] * transformationMatrix[1][2] * transformationMatrix[2][3] - 
                					 transformationMatrix[3][1] * transformationMatrix[1][3] * transformationMatrix[2][2];

    inverseTransformationMatrix[0][1] = -transformationMatrix[0][1] * transformationMatrix[2][2] * transformationMatrix[3][3] + 
                					 transformationMatrix[0][1] * transformationMatrix[2][3] * transformationMatrix[3][2] + 
                					 transformationMatrix[2][1] * transformationMatrix[0][2] * transformationMatrix[3][3] - 
                					 transformationMatrix[2][1] * transformationMatrix[0][3] * transformationMatrix[3][2] - 
                					 transformationMatrix[3][1] * transformationMatrix[0][2] * transformationMatrix[2][3] + 
                					 transformationMatrix[3][1] * transformationMatrix[0][3] * transformationMatrix[2][2];

    inverseTransformationMatrix[1][0] = -transformationMatrix[1][0] * transformationMatrix[2][2] * transformationMatrix[3][3] + 
                					 transformationMatrix[1][0] * transformationMatrix[2][3] * transformationMatrix[3][2] + 
                					 transformationMatrix[2][0] * transformationMatrix[1][2] * transformationMatrix[3][3] - 
                					 transformationMatrix[2][0] * transformationMatrix[1][3] * transformationMatrix[3][2] - 
                					 transformationMatrix[3][0] * transformationMatrix[1][2] * transformationMatrix[2][3] + 
                					 transformationMatrix[3][0] * transformationMatrix[1][3] * transformationMatrix[2][2];

    inverseTransformationMatrix[2][0] =  transformationMatrix[1][0] * transformationMatrix[2][1] * transformationMatrix[3][3] - 
                					 transformationMatrix[1][0] * transformationMatrix[2][3] * transformationMatrix[3][1] - 
                					 transformationMatrix[2][0] * transformationMatrix[1][1] * transformationMatrix[3][3] + 
                					 transformationMatrix[2][0] * transformationMatrix[1][3] * transformationMatrix[3][1] + 
                					 transformationMatrix[3][0] * transformationMatrix[1][1] * transformationMatrix[2][3] - 
                					 transformationMatrix[3][0] * transformationMatrix[1][3] * transformationMatrix[2][1];

    inverseTransformationMatrix[3][0] = -transformationMatrix[1][0] * transformationMatrix[2][1] * transformationMatrix[3][2] + 
                					 transformationMatrix[1][0] * transformationMatrix[2][2] * transformationMatrix[3][1] +
                					 transformationMatrix[2][0] * transformationMatrix[1][1] * transformationMatrix[3][2] - 
                					 transformationMatrix[2][0] * transformationMatrix[1][2] * transformationMatrix[3][1] - 
                					 transformationMatrix[3][0] * transformationMatrix[1][1] * transformationMatrix[2][2] + 
                					 transformationMatrix[3][0] * transformationMatrix[1][2] * transformationMatrix[2][1];



    inverseTransformationMatrix[1][1] =  transformationMatrix[0][0] * transformationMatrix[2][2] * transformationMatrix[3][3] - 
                					 transformationMatrix[0][0] * transformationMatrix[2][3] * transformationMatrix[3][2] - 
                					 transformationMatrix[2][0] * transformationMatrix[0][2] * transformationMatrix[3][3] + 
                					 transformationMatrix[2][0] * transformationMatrix[0][3] * transformationMatrix[3][2] + 
                					 transformationMatrix[3][0] * transformationMatrix[0][2] * transformationMatrix[2][3] - 
                					 transformationMatrix[3][0] * transformationMatrix[0][3] * transformationMatrix[2][2];

    inverseTransformationMatrix[2][1] = -transformationMatrix[0][0] * transformationMatrix[2][1] * transformationMatrix[3][3] + 
                					 transformationMatrix[0][0] * transformationMatrix[2][3] * transformationMatrix[3][1] + 
                					 transformationMatrix[2][0] * transformationMatrix[0][1] * transformationMatrix[3][3] - 
                					 transformationMatrix[2][0] * transformationMatrix[0][3] * transformationMatrix[3][1] - 
                					 transformationMatrix[3][0] * transformationMatrix[0][1] * transformationMatrix[2][3] + 
                					 transformationMatrix[3][0] * transformationMatrix[0][3] * transformationMatrix[2][1];

    inverseTransformationMatrix[3][1] =  transformationMatrix[0][0] * transformationMatrix[2][1] * transformationMatrix[3][2] - 
                					 transformationMatrix[0][0] * transformationMatrix[2][2] * transformationMatrix[3][1] - 
                					 transformationMatrix[2][0] * transformationMatrix[0][1] * transformationMatrix[3][2] + 
                					 transformationMatrix[2][0] * transformationMatrix[0][2] * transformationMatrix[3][1] + 
                					 transformationMatrix[3][0] * transformationMatrix[0][1] * transformationMatrix[2][2] - 
                					 transformationMatrix[3][0] * transformationMatrix[0][2] * transformationMatrix[2][1];

    inverseTransformationMatrix[0][2] =  transformationMatrix[0][1] * transformationMatrix[1][2] * transformationMatrix[3][3] - 
                					 transformationMatrix[0][1] * transformationMatrix[1][3] * transformationMatrix[3][2] - 
                					 transformationMatrix[1][1] * transformationMatrix[0][2] * transformationMatrix[3][3] + 
                					 transformationMatrix[1][1] * transformationMatrix[0][3] * transformationMatrix[3][2] + 
                					 transformationMatrix[3][1] * transformationMatrix[0][2] * transformationMatrix[1][3] - 
                					 transformationMatrix[3][1] * transformationMatrix[0][3] * transformationMatrix[1][2];
                					 
    inverseTransformationMatrix[0][3] = -transformationMatrix[0][1] * transformationMatrix[1][2] * transformationMatrix[2][3] + 
                 					 transformationMatrix[0][1] * transformationMatrix[1][3] * transformationMatrix[2][2] + 
              						 transformationMatrix[1][1] * transformationMatrix[0][2] * transformationMatrix[2][3] - 
              						 transformationMatrix[1][1] * transformationMatrix[0][3] * transformationMatrix[2][2] - 
              						 transformationMatrix[2][1] * transformationMatrix[0][2] * transformationMatrix[1][3] + 
              						 transformationMatrix[2][1] * transformationMatrix[0][3] * transformationMatrix[1][2];


    inverseTransformationMatrix[1][2] = -transformationMatrix[0][0] * transformationMatrix[1][2] * transformationMatrix[3][3] + 
                					 transformationMatrix[0][0] * transformationMatrix[1][3] * transformationMatrix[3][2] + 
                					 transformationMatrix[1][0] * transformationMatrix[0][2] * transformationMatrix[3][3] - 
                					 transformationMatrix[1][0] * transformationMatrix[0][3] * transformationMatrix[3][2] - 
                					 transformationMatrix[3][0] * transformationMatrix[0][2] * transformationMatrix[1][3] + 
                					 transformationMatrix[3][0] * transformationMatrix[0][3] * transformationMatrix[1][2];

    inverseTransformationMatrix[2][2] =  transformationMatrix[0][0] * transformationMatrix[1][1] * transformationMatrix[3][3] - 
                					 transformationMatrix[0][0] * transformationMatrix[1][3] * transformationMatrix[3][1] - 
                					 transformationMatrix[1][0] * transformationMatrix[0][1] * transformationMatrix[3][3] + 
                					 transformationMatrix[1][0] * transformationMatrix[0][3] * transformationMatrix[3][1] + 
                					 transformationMatrix[3][0] * transformationMatrix[0][1] * transformationMatrix[1][3] - 
                					 transformationMatrix[3][0] * transformationMatrix[0][3] * transformationMatrix[1][1];

    inverseTransformationMatrix[3][2] = -transformationMatrix[0][0] * transformationMatrix[1][1] * transformationMatrix[3][2] + 
                					 transformationMatrix[0][0] * transformationMatrix[1][2] * transformationMatrix[3][1] + 
                					 transformationMatrix[1][0] * transformationMatrix[0][1] * transformationMatrix[3][2] - 
                					 transformationMatrix[1][0] * transformationMatrix[0][2] * transformationMatrix[3][1] - 
                					 transformationMatrix[3][0] * transformationMatrix[0][1] * transformationMatrix[1][2] + 
                					 transformationMatrix[3][0] * transformationMatrix[0][2] * transformationMatrix[1][1];


    inverseTransformationMatrix[1][3] =  transformationMatrix[0][0] * transformationMatrix[1][2] * transformationMatrix[2][3] - 
                 					 transformationMatrix[0][0] * transformationMatrix[1][3] * transformationMatrix[2][2] - 
                 					 transformationMatrix[1][0] * transformationMatrix[0][2] * transformationMatrix[2][3] + 
                 					 transformationMatrix[1][0] * transformationMatrix[0][3] * transformationMatrix[2][2] + 
                 					 transformationMatrix[2][0] * transformationMatrix[0][2] * transformationMatrix[1][3] - 
                 					 transformationMatrix[2][0] * transformationMatrix[0][3] * transformationMatrix[1][2];

    inverseTransformationMatrix[2][3] = -transformationMatrix[0][0] * transformationMatrix[1][1] * transformationMatrix[2][3] + 
                 					 transformationMatrix[0][0] * transformationMatrix[1][3] * transformationMatrix[2][1] + 
                 					 transformationMatrix[1][0] * transformationMatrix[0][1] * transformationMatrix[2][3] - 
                 					 transformationMatrix[1][0] * transformationMatrix[0][3] * transformationMatrix[2][1] - 
                 					 transformationMatrix[2][0] * transformationMatrix[0][1] * transformationMatrix[1][3] + 
                 					 transformationMatrix[2][0] * transformationMatrix[0][3] * transformationMatrix[1][1];

    inverseTransformationMatrix[3][3] =  transformationMatrix[0][0] * transformationMatrix[1][1] * transformationMatrix[2][2] - 
                 					 transformationMatrix[0][0] * transformationMatrix[1][2] * transformationMatrix[2][1] - 
                 					 transformationMatrix[1][0] * transformationMatrix[0][1] * transformationMatrix[2][2] + 
                 					 transformationMatrix[1][0] * transformationMatrix[0][2] * transformationMatrix[2][1] + 
               						 transformationMatrix[2][0] * transformationMatrix[0][1] * transformationMatrix[1][2] - 
                 					 transformationMatrix[2][0] * transformationMatrix[0][2] * transformationMatrix[1][1];

    det = transformationMatrix[0][0] * inverseTransformationMatrix[0][0] + 
    	  transformationMatrix[0][1] * inverseTransformationMatrix[1][0] + 
    	  transformationMatrix[0][2] * inverseTransformationMatrix[2][0] + 
    	  transformationMatrix[0][3] * inverseTransformationMatrix[3][0];

    if (det == 0){
    	std::cout << "Error Determinant 0\n";
    	exit (EXIT_FAILURE);
    }

    det = 1.0 / det;

    for (j = 0; j < 4; j++){
    	for (i = 0; i < 4; i++){
        	inverseTransformationMatrix[j][i] = inverseTransformationMatrix[j][i] * det;
        }
    }

}
tuple matrix::mutiplyinverse(const tuple& t){
	int i,j;
	tuple outPutMatrix;
	outPutMatrix.e[0]= t.e[0]*inverseTransformationMatrix[0][0]+ t.e[1]*inverseTransformationMatrix[0][1]+ 
					   t.e[2]*inverseTransformationMatrix[0][2]+ t.e[3]*inverseTransformationMatrix[0][3];
	outPutMatrix.e[1]= t.e[0]*inverseTransformationMatrix[1][0]+ t.e[1]*inverseTransformationMatrix[1][1]+ 
					   t.e[2]*inverseTransformationMatrix[1][2]+ t.e[3]*inverseTransformationMatrix[1][3];
	outPutMatrix.e[2]= t.e[0]*inverseTransformationMatrix[2][0]+ t.e[1]*inverseTransformationMatrix[2][1]+ 
					   t.e[2]*inverseTransformationMatrix[2][2]+ t.e[3]*inverseTransformationMatrix[2][3];
	outPutMatrix.e[3]= t.e[0]*inverseTransformationMatrix[3][0]+ t.e[1]*inverseTransformationMatrix[3][1]+ 
					   t.e[2]*inverseTransformationMatrix[3][2]+ t.e[3]*inverseTransformationMatrix[3][3];
	return outPutMatrix;
}
inline matrix translation(const tuple& t){
	matrix mout;
	mout.setIdentity();
	mout.transformationMatrix[0][3]=t.e[0];
	mout.transformationMatrix[1][3]=t.e[1];
	mout.transformationMatrix[2][3]=t.e[2];
	return mout;
}
inline matrix scale(const tuple& t){
	matrix mout;
	mout.setIdentity();
	mout.transformationMatrix[0][0]=t.e[0];
	mout.transformationMatrix[1][1]=t.e[1];
	mout.transformationMatrix[2][2]=t.e[2];
	return mout;
}
inline matrix rotatex(float angle){
	matrix mout;
	mout.setIdentity();
	mout.transformationMatrix[1][1]=cos(angle);
	mout.transformationMatrix[1][2]=-sin(angle);
	mout.transformationMatrix[2][1]=sin(angle);
	mout.transformationMatrix[2][2]=cos(angle);
	return mout;
}
inline matrix rotatey(float angle){
	matrix mout;
	mout.setIdentity();
	mout.transformationMatrix[0][0]=cos(angle);
	mout.transformationMatrix[0][2]=sin(angle);
	mout.transformationMatrix[2][0]=-sin(angle);
	mout.transformationMatrix[2][2]=cos(angle);
	return mout;
}
inline matrix rotatez(float angle){
	matrix mout;
	mout.setIdentity();
	mout.transformationMatrix[0][0]=cos(angle);
	mout.transformationMatrix[0][1]=-sin(angle);
	mout.transformationMatrix[1][0]=sin(angle);
	mout.transformationMatrix[1][1]=cos(angle);
	return mout;
}
inline matrix shearing(float& xy,float& xz, float& yx, float& yz, float& zx, float& zy){
	matrix mout;
	mout.transformationMatrix[0][0]=1;
	mout.transformationMatrix[0][1]=xy;
	mout.transformationMatrix[0][2]=xz;
	mout.transformationMatrix[0][3]=0;

	mout.transformationMatrix[1][0]=yx;
	mout.transformationMatrix[1][1]=1;
	mout.transformationMatrix[1][2]=yz;
	mout.transformationMatrix[1][3]=0;

	mout.transformationMatrix[2][0]=zx;
	mout.transformationMatrix[2][1]=zy;
	mout.transformationMatrix[2][2]=1;
	mout.transformationMatrix[2][3]=0;

	mout.transformationMatrix[3][0]=0;
	mout.transformationMatrix[3][1]=0;
	mout.transformationMatrix[3][2]=0;
	mout.transformationMatrix[3][3]=1;
	return mout;
}
inline matrix operator*(const matrix& m1, const matrix& m2){
	int i,j;
	matrix outPutMatrix;
	for (j=0;j<4;j++){
		outPutMatrix.transformationMatrix[j][0]= m1.transformationMatrix[j][0]*m2.transformationMatrix[0][0]+ 
												 m1.transformationMatrix[j][1]*m2.transformationMatrix[1][0]+ 
												 m1.transformationMatrix[j][2]*m2.transformationMatrix[2][0]+ 
												 m1.transformationMatrix[j][3]*m2.transformationMatrix[3][0];
		outPutMatrix.transformationMatrix[j][1]= m1.transformationMatrix[j][0]*m2.transformationMatrix[0][1]+ 
												 m1.transformationMatrix[j][1]*m2.transformationMatrix[1][1]+ 
												 m1.transformationMatrix[j][2]*m2.transformationMatrix[2][1]+ 
												 m1.transformationMatrix[j][3]*m2.transformationMatrix[3][1];
		outPutMatrix.transformationMatrix[j][2]= m1.transformationMatrix[j][0]*m2.transformationMatrix[0][2]+ 
												 m1.transformationMatrix[j][1]*m2.transformationMatrix[1][2]+ 
												 m1.transformationMatrix[j][2]*m2.transformationMatrix[2][2]+ 
												 m1.transformationMatrix[j][3]*m2.transformationMatrix[3][2];
		outPutMatrix.transformationMatrix[j][3]= m1.transformationMatrix[j][0]*m2.transformationMatrix[0][3]+ 
												 m1.transformationMatrix[j][1]*m2.transformationMatrix[1][3]+ 
												 m1.transformationMatrix[j][2]*m2.transformationMatrix[2][3]+ 
												 m1.transformationMatrix[j][3]*m2.transformationMatrix[3][3];
	}
	return outPutMatrix;
}
inline tuple operator*(const tuple& t,const matrix& m1){
	int i,j;
	tuple outPutMatrix;
	outPutMatrix.e[0]= t.e[0]*m1.transformationMatrix[0][0]+ t.e[1]*m1.transformationMatrix[0][1]+ 
					   t.e[2]*m1.transformationMatrix[0][2]+ t.e[3]*m1.transformationMatrix[0][3];
	outPutMatrix.e[1]= t.e[0]*m1.transformationMatrix[1][0]+ t.e[1]*m1.transformationMatrix[1][1]+ 
					   t.e[2]*m1.transformationMatrix[1][2]+ t.e[3]*m1.transformationMatrix[1][3];
	outPutMatrix.e[2]= t.e[0]*m1.transformationMatrix[2][0]+ t.e[1]*m1.transformationMatrix[2][1]+ 
					   t.e[2]*m1.transformationMatrix[2][2]+ t.e[3]*m1.transformationMatrix[2][3];
	outPutMatrix.e[3]= t.e[0]*m1.transformationMatrix[3][0]+ t.e[1]*m1.transformationMatrix[3][1]+ 
					   t.e[2]*m1.transformationMatrix[3][2]+ t.e[3]*m1.transformationMatrix[3][3];
	return outPutMatrix;
}

inline matrix invertMatrix(const matrix& m1){
    float det;
    int i,j;
	matrix m2;
    m2.transformationMatrix[0][0] =  m1.transformationMatrix[1][1] * m1.transformationMatrix[2][2] * m1.transformationMatrix[3][3] - 
                					 m1.transformationMatrix[1][1] * m1.transformationMatrix[2][3] * m1.transformationMatrix[3][2] - 
                					 m1.transformationMatrix[2][1] * m1.transformationMatrix[1][2] * m1.transformationMatrix[3][3] + 
                					 m1.transformationMatrix[2][1] * m1.transformationMatrix[1][3] * m1.transformationMatrix[3][2] +
                					 m1.transformationMatrix[3][1] * m1.transformationMatrix[1][2] * m1.transformationMatrix[2][3] - 
                					 m1.transformationMatrix[3][1] * m1.transformationMatrix[1][3] * m1.transformationMatrix[2][2];

    m2.transformationMatrix[0][1] = -m1.transformationMatrix[0][1] * m1.transformationMatrix[2][2] * m1.transformationMatrix[3][3] + 
                					 m1.transformationMatrix[0][1] * m1.transformationMatrix[2][3] * m1.transformationMatrix[3][2] + 
                					 m1.transformationMatrix[2][1] * m1.transformationMatrix[0][2] * m1.transformationMatrix[3][3] - 
                					 m1.transformationMatrix[2][1] * m1.transformationMatrix[0][3] * m1.transformationMatrix[3][2] - 
                					 m1.transformationMatrix[3][1] * m1.transformationMatrix[0][2] * m1.transformationMatrix[2][3] + 
                					 m1.transformationMatrix[3][1] * m1.transformationMatrix[0][3] * m1.transformationMatrix[2][2];

    m2.transformationMatrix[1][0] = -m1.transformationMatrix[1][0] * m1.transformationMatrix[2][2] * m1.transformationMatrix[3][3] + 
                					 m1.transformationMatrix[1][0] * m1.transformationMatrix[2][3] * m1.transformationMatrix[3][2] + 
                					 m1.transformationMatrix[2][0] * m1.transformationMatrix[1][2] * m1.transformationMatrix[3][3] - 
                					 m1.transformationMatrix[2][0] * m1.transformationMatrix[1][3] * m1.transformationMatrix[3][2] - 
                					 m1.transformationMatrix[3][0] * m1.transformationMatrix[1][2] * m1.transformationMatrix[2][3] + 
                					 m1.transformationMatrix[3][0] * m1.transformationMatrix[1][3] * m1.transformationMatrix[2][2];

    m2.transformationMatrix[2][0] =  m1.transformationMatrix[1][0] * m1.transformationMatrix[2][1] * m1.transformationMatrix[3][3] - 
                					 m1.transformationMatrix[1][0] * m1.transformationMatrix[2][3] * m1.transformationMatrix[3][1] - 
                					 m1.transformationMatrix[2][0] * m1.transformationMatrix[1][1] * m1.transformationMatrix[3][3] + 
                					 m1.transformationMatrix[2][0] * m1.transformationMatrix[1][3] * m1.transformationMatrix[3][1] + 
                					 m1.transformationMatrix[3][0] * m1.transformationMatrix[1][1] * m1.transformationMatrix[2][3] - 
                					 m1.transformationMatrix[3][0] * m1.transformationMatrix[1][3] * m1.transformationMatrix[2][1];

    m2.transformationMatrix[3][0] = -m1.transformationMatrix[1][0] * m1.transformationMatrix[2][1] * m1.transformationMatrix[3][2] + 
                					 m1.transformationMatrix[1][0] * m1.transformationMatrix[2][2] * m1.transformationMatrix[3][1] +
                					 m1.transformationMatrix[2][0] * m1.transformationMatrix[1][1] * m1.transformationMatrix[3][2] - 
                					 m1.transformationMatrix[2][0] * m1.transformationMatrix[1][2] * m1.transformationMatrix[3][1] - 
                					 m1.transformationMatrix[3][0] * m1.transformationMatrix[1][1] * m1.transformationMatrix[2][2] + 
                					 m1.transformationMatrix[3][0] * m1.transformationMatrix[1][2] * m1.transformationMatrix[2][1];



    m2.transformationMatrix[1][1] =  m1.transformationMatrix[0][0] * m1.transformationMatrix[2][2] * m1.transformationMatrix[3][3] - 
                					 m1.transformationMatrix[0][0] * m1.transformationMatrix[2][3] * m1.transformationMatrix[3][2] - 
                					 m1.transformationMatrix[2][0] * m1.transformationMatrix[0][2] * m1.transformationMatrix[3][3] + 
                					 m1.transformationMatrix[2][0] * m1.transformationMatrix[0][3] * m1.transformationMatrix[3][2] + 
                					 m1.transformationMatrix[3][0] * m1.transformationMatrix[0][2] * m1.transformationMatrix[2][3] - 
                					 m1.transformationMatrix[3][0] * m1.transformationMatrix[0][3] * m1.transformationMatrix[2][2];

    m2.transformationMatrix[2][1] = -m1.transformationMatrix[0][0] * m1.transformationMatrix[2][1] * m1.transformationMatrix[3][3] + 
                					 m1.transformationMatrix[0][0] * m1.transformationMatrix[2][3] * m1.transformationMatrix[3][1] + 
                					 m1.transformationMatrix[2][0] * m1.transformationMatrix[0][1] * m1.transformationMatrix[3][3] - 
                					 m1.transformationMatrix[2][0] * m1.transformationMatrix[0][3] * m1.transformationMatrix[3][1] - 
                					 m1.transformationMatrix[3][0] * m1.transformationMatrix[0][1] * m1.transformationMatrix[2][3] + 
                					 m1.transformationMatrix[3][0] * m1.transformationMatrix[0][3] * m1.transformationMatrix[2][1];

    m2.transformationMatrix[3][1] =  m1.transformationMatrix[0][0] * m1.transformationMatrix[2][1] * m1.transformationMatrix[3][2] - 
                					 m1.transformationMatrix[0][0] * m1.transformationMatrix[2][2] * m1.transformationMatrix[3][1] - 
                					 m1.transformationMatrix[2][0] * m1.transformationMatrix[0][1] * m1.transformationMatrix[3][2] + 
                					 m1.transformationMatrix[2][0] * m1.transformationMatrix[0][2] * m1.transformationMatrix[3][1] + 
                					 m1.transformationMatrix[3][0] * m1.transformationMatrix[0][1] * m1.transformationMatrix[2][2] - 
                					 m1.transformationMatrix[3][0] * m1.transformationMatrix[0][2] * m1.transformationMatrix[2][1];

    m2.transformationMatrix[0][2] =  m1.transformationMatrix[0][1] * m1.transformationMatrix[1][2] * m1.transformationMatrix[3][3] - 
                					 m1.transformationMatrix[0][1] * m1.transformationMatrix[1][3] * m1.transformationMatrix[3][2] - 
                					 m1.transformationMatrix[1][1] * m1.transformationMatrix[0][2] * m1.transformationMatrix[3][3] + 
                					 m1.transformationMatrix[1][1] * m1.transformationMatrix[0][3] * m1.transformationMatrix[3][2] + 
                					 m1.transformationMatrix[3][1] * m1.transformationMatrix[0][2] * m1.transformationMatrix[1][3] - 
                					 m1.transformationMatrix[3][1] * m1.transformationMatrix[0][3] * m1.transformationMatrix[1][2];
                					 
    m2.transformationMatrix[0][3] = -m1.transformationMatrix[0][1] * m1.transformationMatrix[1][2] * m1.transformationMatrix[2][3] + 
                 					 m1.transformationMatrix[0][1] * m1.transformationMatrix[1][3] * m1.transformationMatrix[2][2] + 
              						 m1.transformationMatrix[1][1] * m1.transformationMatrix[0][2] * m1.transformationMatrix[2][3] - 
              						 m1.transformationMatrix[1][1] * m1.transformationMatrix[0][3] * m1.transformationMatrix[2][2] - 
              						 m1.transformationMatrix[2][1] * m1.transformationMatrix[0][2] * m1.transformationMatrix[1][3] + 
              						 m1.transformationMatrix[2][1] * m1.transformationMatrix[0][3] * m1.transformationMatrix[1][2];


    m2.transformationMatrix[1][2] = -m1.transformationMatrix[0][0] * m1.transformationMatrix[1][2] * m1.transformationMatrix[3][3] + 
                					 m1.transformationMatrix[0][0] * m1.transformationMatrix[1][3] * m1.transformationMatrix[3][2] + 
                					 m1.transformationMatrix[1][0] * m1.transformationMatrix[0][2] * m1.transformationMatrix[3][3] - 
                					 m1.transformationMatrix[1][0] * m1.transformationMatrix[0][3] * m1.transformationMatrix[3][2] - 
                					 m1.transformationMatrix[3][0] * m1.transformationMatrix[0][2] * m1.transformationMatrix[1][3] + 
                					 m1.transformationMatrix[3][0] * m1.transformationMatrix[0][3] * m1.transformationMatrix[1][2];

    m2.transformationMatrix[2][2] =  m1.transformationMatrix[0][0] * m1.transformationMatrix[1][1] * m1.transformationMatrix[3][3] - 
                					 m1.transformationMatrix[0][0] * m1.transformationMatrix[1][3] * m1.transformationMatrix[3][1] - 
                					 m1.transformationMatrix[1][0] * m1.transformationMatrix[0][1] * m1.transformationMatrix[3][3] + 
                					 m1.transformationMatrix[1][0] * m1.transformationMatrix[0][3] * m1.transformationMatrix[3][1] + 
                					 m1.transformationMatrix[3][0] * m1.transformationMatrix[0][1] * m1.transformationMatrix[1][3] - 
                					 m1.transformationMatrix[3][0] * m1.transformationMatrix[0][3] * m1.transformationMatrix[1][1];

    m2.transformationMatrix[3][2] = -m1.transformationMatrix[0][0] * m1.transformationMatrix[1][1] * m1.transformationMatrix[3][2] + 
                					 m1.transformationMatrix[0][0] * m1.transformationMatrix[1][2] * m1.transformationMatrix[3][1] + 
                					 m1.transformationMatrix[1][0] * m1.transformationMatrix[0][1] * m1.transformationMatrix[3][2] - 
                					 m1.transformationMatrix[1][0] * m1.transformationMatrix[0][2] * m1.transformationMatrix[3][1] - 
                					 m1.transformationMatrix[3][0] * m1.transformationMatrix[0][1] * m1.transformationMatrix[1][2] + 
                					 m1.transformationMatrix[3][0] * m1.transformationMatrix[0][2] * m1.transformationMatrix[1][1];


    m2.transformationMatrix[1][3] =  m1.transformationMatrix[0][0] * m1.transformationMatrix[1][2] * m1.transformationMatrix[2][3] - 
                 					 m1.transformationMatrix[0][0] * m1.transformationMatrix[1][3] * m1.transformationMatrix[2][2] - 
                 					 m1.transformationMatrix[1][0] * m1.transformationMatrix[0][2] * m1.transformationMatrix[2][3] + 
                 					 m1.transformationMatrix[1][0] * m1.transformationMatrix[0][3] * m1.transformationMatrix[2][2] + 
                 					 m1.transformationMatrix[2][0] * m1.transformationMatrix[0][2] * m1.transformationMatrix[1][3] - 
                 					 m1.transformationMatrix[2][0] * m1.transformationMatrix[0][3] * m1.transformationMatrix[1][2];

    m2.transformationMatrix[2][3] = -m1.transformationMatrix[0][0] * m1.transformationMatrix[1][1] * m1.transformationMatrix[2][3] + 
                 					 m1.transformationMatrix[0][0] * m1.transformationMatrix[1][3] * m1.transformationMatrix[2][1] + 
                 					 m1.transformationMatrix[1][0] * m1.transformationMatrix[0][1] * m1.transformationMatrix[2][3] - 
                 					 m1.transformationMatrix[1][0] * m1.transformationMatrix[0][3] * m1.transformationMatrix[2][1] - 
                 					 m1.transformationMatrix[2][0] * m1.transformationMatrix[0][1] * m1.transformationMatrix[1][3] + 
                 					 m1.transformationMatrix[2][0] * m1.transformationMatrix[0][3] * m1.transformationMatrix[1][1];

    m2.transformationMatrix[3][3] =  m1.transformationMatrix[0][0] * m1.transformationMatrix[1][1] * m1.transformationMatrix[2][2] - 
                 					 m1.transformationMatrix[0][0] * m1.transformationMatrix[1][2] * m1.transformationMatrix[2][1] - 
                 					 m1.transformationMatrix[1][0] * m1.transformationMatrix[0][1] * m1.transformationMatrix[2][2] + 
                 					 m1.transformationMatrix[1][0] * m1.transformationMatrix[0][2] * m1.transformationMatrix[2][1] + 
               						 m1.transformationMatrix[2][0] * m1.transformationMatrix[0][1] * m1.transformationMatrix[1][2] - 
                 					 m1.transformationMatrix[2][0] * m1.transformationMatrix[0][2] * m1.transformationMatrix[1][1];

    det = m1.transformationMatrix[0][0] * m2.transformationMatrix[0][0] + 
    	  m1.transformationMatrix[0][1] * m2.transformationMatrix[1][0] + 
    	  m1.transformationMatrix[0][2] * m2.transformationMatrix[2][0] + 
    	  m1.transformationMatrix[0][3] * m2.transformationMatrix[3][0];

    if (det == 0){
    	std::cout << "Error Determinant 0\n";
    	exit (EXIT_FAILURE);
    }

    det = 1.0 / det;

    for (j = 0; j < 4; j++){
    	for (i = 0; i < 4; i++){
        	m2.transformationMatrix[j][i] = m2.transformationMatrix[j][i] * det;
        }
    }
    return m2;
}
#endif