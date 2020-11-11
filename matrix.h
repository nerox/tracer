#ifndef MATRIX
#define MATRIX
#include <math.h>
#include <iostream>
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include "tuple.h"
class matrix {
public:
	float transformationMatrix [4*4];
	float inverseTransformationMatrix [4*4];
	float transPoseMatrix [4*4];

	matrix(){
	}
	matrix(float i0, float i1,float i2, float i3,
		   float i4, float i5,float i6, float i7,
		   float i8, float i9,float i10, float i11,
		   float i12, float i13,float i14, float i15){

		transformationMatrix[0]=i0;
		transformationMatrix[1]=i1;
		transformationMatrix[2]=i2;
		transformationMatrix[3]=i3;

		transformationMatrix[4]=i4;
		transformationMatrix[5]=i5;
		transformationMatrix[6]=i6;
		transformationMatrix[7]=i7;

		transformationMatrix[8]=i8;
		transformationMatrix[9]=i9;
		transformationMatrix[10]=i10;
		transformationMatrix[11]=i11;

		transformationMatrix[12]=i12;
		transformationMatrix[13]=i13;
		transformationMatrix[14]=i14;
		transformationMatrix[15]=i15;

	}
	void setIdentity(){
		transformationMatrix[0]=1;
		transformationMatrix[1]=0;
		transformationMatrix[2]=0;
		transformationMatrix[3]=0;

		transformationMatrix[4]=0;
		transformationMatrix[5]=1;
		transformationMatrix[6]=0;
		transformationMatrix[7]=0;

		transformationMatrix[8]=0;
		transformationMatrix[9]=0;
		transformationMatrix[10]=1;
		transformationMatrix[11]=0;

		transformationMatrix[12]=0;
		transformationMatrix[13]=0;
		transformationMatrix[14]=0;
		transformationMatrix[15]=1;

	}
	void InverseTranspose();
	void invertMatrix();
	tuple mutiplyinverse(const tuple& t);
	tuple mutiplyinverseTanspose(const tuple& t);
	void transpose();
};
void printmematrix(const matrix& m){
	std::cout << m.transformationMatrix[0]<< " "<<m.transformationMatrix[1]<< " "<< m.transformationMatrix[2]<< " "<<m.transformationMatrix[3]<<"\n";
	std::cout << m.transformationMatrix[4]<< " "<<m.transformationMatrix[5]<< " "<< m.transformationMatrix[6]<< " "<<m.transformationMatrix[7]<<"\n";
	std::cout << m.transformationMatrix[8]<< " "<<m.transformationMatrix[9]<< " "<< m.transformationMatrix[10]<< " "<<m.transformationMatrix[11]<<"\n";
	std::cout << m.transformationMatrix[12]<< " "<<m.transformationMatrix[13]<< " "<< m.transformationMatrix[14]<< " "<<m.transformationMatrix[15]<<"\n";

}
void matrix::InverseTranspose(){
	transPoseMatrix[0]=inverseTransformationMatrix[0];
	transPoseMatrix[1]=inverseTransformationMatrix[4];
	transPoseMatrix[2]=inverseTransformationMatrix[8];
	transPoseMatrix[3]=inverseTransformationMatrix[12];

	transPoseMatrix[4]=inverseTransformationMatrix[1];
	transPoseMatrix[5]=inverseTransformationMatrix[5];
	transPoseMatrix[6]=inverseTransformationMatrix[9];
	transPoseMatrix[7]=inverseTransformationMatrix[13];

	transPoseMatrix[8]=inverseTransformationMatrix[2];
	transPoseMatrix[9]=inverseTransformationMatrix[6];
	transPoseMatrix[10]=inverseTransformationMatrix[10];
	transPoseMatrix[11]=inverseTransformationMatrix[14];

	transPoseMatrix[12]=inverseTransformationMatrix[3];
	transPoseMatrix[13]=inverseTransformationMatrix[7];
	transPoseMatrix[14]=inverseTransformationMatrix[11];
	transPoseMatrix[15]=inverseTransformationMatrix[15];
}
void matrix::invertMatrix(){
    float det;
    int i,j;
    inverseTransformationMatrix[0] =  transformationMatrix[5] * transformationMatrix[10] * transformationMatrix[15] - 
                					 transformationMatrix[5] * transformationMatrix[11] * transformationMatrix[14] - 
                					 transformationMatrix[9] * transformationMatrix[6] * transformationMatrix[15] + 
                					 transformationMatrix[9] * transformationMatrix[7] * transformationMatrix[14] +
                					 transformationMatrix[13] * transformationMatrix[6] * transformationMatrix[11] - 
                					 transformationMatrix[13] * transformationMatrix[7] * transformationMatrix[10];

    inverseTransformationMatrix[1] = -transformationMatrix[1] * transformationMatrix[10] * transformationMatrix[15] + 
                					 transformationMatrix[1] * transformationMatrix[11] * transformationMatrix[14] + 
                					 transformationMatrix[9] * transformationMatrix[2] * transformationMatrix[15] - 
                					 transformationMatrix[9] * transformationMatrix[3] * transformationMatrix[14] - 
                					 transformationMatrix[13] * transformationMatrix[2] * transformationMatrix[11] + 
                					 transformationMatrix[13] * transformationMatrix[3] * transformationMatrix[10];

    inverseTransformationMatrix[4] = -transformationMatrix[4] * transformationMatrix[10] * transformationMatrix[15] + 
                					 transformationMatrix[4] * transformationMatrix[11] * transformationMatrix[14] + 
                					 transformationMatrix[8] * transformationMatrix[6] * transformationMatrix[15] - 
                					 transformationMatrix[8] * transformationMatrix[7] * transformationMatrix[14] - 
                					 transformationMatrix[12] * transformationMatrix[6] * transformationMatrix[11] + 
                					 transformationMatrix[12] * transformationMatrix[7] * transformationMatrix[10];

    inverseTransformationMatrix[8] =  transformationMatrix[4] * transformationMatrix[9] * transformationMatrix[15] - 
                					 transformationMatrix[4] * transformationMatrix[11] * transformationMatrix[13] - 
                					 transformationMatrix[8] * transformationMatrix[5] * transformationMatrix[15] + 
                					 transformationMatrix[8] * transformationMatrix[7] * transformationMatrix[13] + 
                					 transformationMatrix[12] * transformationMatrix[5] * transformationMatrix[11] - 
                					 transformationMatrix[12] * transformationMatrix[7] * transformationMatrix[9];

    inverseTransformationMatrix[12] = -transformationMatrix[4] * transformationMatrix[9] * transformationMatrix[14] + 
                					 transformationMatrix[4] * transformationMatrix[10] * transformationMatrix[13] +
                					 transformationMatrix[8] * transformationMatrix[5] * transformationMatrix[14] - 
                					 transformationMatrix[8] * transformationMatrix[6] * transformationMatrix[13] - 
                					 transformationMatrix[12] * transformationMatrix[5] * transformationMatrix[10] + 
                					 transformationMatrix[12] * transformationMatrix[6] * transformationMatrix[9];



    inverseTransformationMatrix[5] =  transformationMatrix[0] * transformationMatrix[10] * transformationMatrix[15] - 
                					 transformationMatrix[0] * transformationMatrix[11] * transformationMatrix[14] - 
                					 transformationMatrix[8] * transformationMatrix[2] * transformationMatrix[15] + 
                					 transformationMatrix[8] * transformationMatrix[3] * transformationMatrix[14] + 
                					 transformationMatrix[12] * transformationMatrix[2] * transformationMatrix[11] - 
                					 transformationMatrix[12] * transformationMatrix[3] * transformationMatrix[10];

    inverseTransformationMatrix[9] = -transformationMatrix[0] * transformationMatrix[9] * transformationMatrix[15] + 
                					 transformationMatrix[0] * transformationMatrix[11] * transformationMatrix[13] + 
                					 transformationMatrix[8] * transformationMatrix[1] * transformationMatrix[15] - 
                					 transformationMatrix[8] * transformationMatrix[3] * transformationMatrix[13] - 
                					 transformationMatrix[12] * transformationMatrix[1] * transformationMatrix[11] + 
                					 transformationMatrix[12] * transformationMatrix[3] * transformationMatrix[9];

    inverseTransformationMatrix[13] =  transformationMatrix[0] * transformationMatrix[9] * transformationMatrix[14] - 
                					 transformationMatrix[0] * transformationMatrix[10] * transformationMatrix[13] - 
                					 transformationMatrix[8] * transformationMatrix[1] * transformationMatrix[14] + 
                					 transformationMatrix[8] * transformationMatrix[2] * transformationMatrix[13] + 
                					 transformationMatrix[12] * transformationMatrix[1] * transformationMatrix[10] - 
                					 transformationMatrix[12] * transformationMatrix[2] * transformationMatrix[9];

    inverseTransformationMatrix[2] =  transformationMatrix[1] * transformationMatrix[6] * transformationMatrix[15] - 
                					 transformationMatrix[1] * transformationMatrix[7] * transformationMatrix[14] - 
                					 transformationMatrix[5] * transformationMatrix[2] * transformationMatrix[15] + 
                					 transformationMatrix[5] * transformationMatrix[3] * transformationMatrix[14] + 
                					 transformationMatrix[13] * transformationMatrix[2] * transformationMatrix[7] - 
                					 transformationMatrix[13] * transformationMatrix[3] * transformationMatrix[6];
                					 
    inverseTransformationMatrix[3] = -transformationMatrix[1] * transformationMatrix[6] * transformationMatrix[11] + 
                 					 transformationMatrix[1] * transformationMatrix[7] * transformationMatrix[10] + 
              						 transformationMatrix[5] * transformationMatrix[2] * transformationMatrix[11] - 
              						 transformationMatrix[5] * transformationMatrix[3] * transformationMatrix[10] - 
              						 transformationMatrix[9] * transformationMatrix[2] * transformationMatrix[7] + 
              						 transformationMatrix[9] * transformationMatrix[3] * transformationMatrix[6];


    inverseTransformationMatrix[6] = -transformationMatrix[0] * transformationMatrix[6] * transformationMatrix[15] + 
                					 transformationMatrix[0] * transformationMatrix[7] * transformationMatrix[14] + 
                					 transformationMatrix[4] * transformationMatrix[2] * transformationMatrix[15] - 
                					 transformationMatrix[4] * transformationMatrix[3] * transformationMatrix[14] - 
                					 transformationMatrix[12] * transformationMatrix[2] * transformationMatrix[7] + 
                					 transformationMatrix[12] * transformationMatrix[3] * transformationMatrix[6];

    inverseTransformationMatrix[10] =  transformationMatrix[0] * transformationMatrix[5] * transformationMatrix[15] - 
                					 transformationMatrix[0] * transformationMatrix[7] * transformationMatrix[13] - 
                					 transformationMatrix[4] * transformationMatrix[1] * transformationMatrix[15] + 
                					 transformationMatrix[4] * transformationMatrix[3] * transformationMatrix[13] + 
                					 transformationMatrix[12] * transformationMatrix[1] * transformationMatrix[7] - 
                					 transformationMatrix[12] * transformationMatrix[3] * transformationMatrix[5];

    inverseTransformationMatrix[14] = -transformationMatrix[0] * transformationMatrix[5] * transformationMatrix[14] + 
                					 transformationMatrix[0] * transformationMatrix[6] * transformationMatrix[13] + 
                					 transformationMatrix[4] * transformationMatrix[1] * transformationMatrix[14] - 
                					 transformationMatrix[4] * transformationMatrix[2] * transformationMatrix[13] - 
                					 transformationMatrix[12] * transformationMatrix[1] * transformationMatrix[6] + 
                					 transformationMatrix[12] * transformationMatrix[2] * transformationMatrix[5];


    inverseTransformationMatrix[7] =  transformationMatrix[0] * transformationMatrix[6] * transformationMatrix[11] - 
                 					 transformationMatrix[0] * transformationMatrix[7] * transformationMatrix[10] - 
                 					 transformationMatrix[4] * transformationMatrix[2] * transformationMatrix[11] + 
                 					 transformationMatrix[4] * transformationMatrix[3] * transformationMatrix[10] + 
                 					 transformationMatrix[8] * transformationMatrix[2] * transformationMatrix[7] - 
                 					 transformationMatrix[8] * transformationMatrix[3] * transformationMatrix[6];

    inverseTransformationMatrix[11] = -transformationMatrix[0] * transformationMatrix[5] * transformationMatrix[11] + 
                 					 transformationMatrix[0] * transformationMatrix[7] * transformationMatrix[9] + 
                 					 transformationMatrix[4] * transformationMatrix[1] * transformationMatrix[11] - 
                 					 transformationMatrix[4] * transformationMatrix[3] * transformationMatrix[9] - 
                 					 transformationMatrix[8] * transformationMatrix[1] * transformationMatrix[7] + 
                 					 transformationMatrix[8] * transformationMatrix[3] * transformationMatrix[5];

    inverseTransformationMatrix[15] =  transformationMatrix[0] * transformationMatrix[5] * transformationMatrix[10] - 
                 					 transformationMatrix[0] * transformationMatrix[6] * transformationMatrix[9] - 
                 					 transformationMatrix[4] * transformationMatrix[1] * transformationMatrix[10] + 
                 					 transformationMatrix[4] * transformationMatrix[2] * transformationMatrix[9] + 
               						 transformationMatrix[8] * transformationMatrix[1] * transformationMatrix[6] - 
                 					 transformationMatrix[8] * transformationMatrix[2] * transformationMatrix[5];

    det = transformationMatrix[0] * inverseTransformationMatrix[0] + 
    	  transformationMatrix[1] * inverseTransformationMatrix[4] + 
    	  transformationMatrix[2] * inverseTransformationMatrix[8] + 
    	  transformationMatrix[3] * inverseTransformationMatrix[12];

    if (det == 0){
    	std::cout << "Error Determinant 0\n";
    	exit (EXIT_FAILURE);
    }

    det = 1.0 / det;

    for (j = 0; j < 4; j++){
    	for (i = 0; i < 4; i++){
        	inverseTransformationMatrix[j*4+i] = inverseTransformationMatrix[j*4+i] * det;
        }
    }

}
tuple matrix::mutiplyinverse(const tuple& t){
	int i,j;
	tuple outPutMatrix;
	outPutMatrix.e[0]= t.e[0]*inverseTransformationMatrix[0]+ t.e[1]*inverseTransformationMatrix[1]+ 
					   t.e[2]*inverseTransformationMatrix[2]+ t.e[3]*inverseTransformationMatrix[3];
	outPutMatrix.e[1]= t.e[0]*inverseTransformationMatrix[4]+ t.e[1]*inverseTransformationMatrix[5]+ 
					   t.e[2]*inverseTransformationMatrix[6]+ t.e[3]*inverseTransformationMatrix[7];
	outPutMatrix.e[2]= t.e[0]*inverseTransformationMatrix[8]+ t.e[1]*inverseTransformationMatrix[9]+ 
					   t.e[2]*inverseTransformationMatrix[10]+ t.e[3]*inverseTransformationMatrix[11];
	outPutMatrix.e[3]= t.e[0]*inverseTransformationMatrix[12]+ t.e[1]*inverseTransformationMatrix[13]+ 
					   t.e[2]*inverseTransformationMatrix[14]+ t.e[3]*inverseTransformationMatrix[15];
	return outPutMatrix;
}
tuple matrix::mutiplyinverseTanspose(const tuple& t){
	int i,j;
	tuple outPutMatrix;
	outPutMatrix.e[0]= t.e[0]*transPoseMatrix[0]+ t.e[1]*transPoseMatrix[1]+ 
					   t.e[2]*transPoseMatrix[2]+ t.e[3]*transPoseMatrix[3];
	outPutMatrix.e[1]= t.e[0]*transPoseMatrix[4]+ t.e[1]*transPoseMatrix[5]+ 
					   t.e[2]*transPoseMatrix[6]+ t.e[3]*transPoseMatrix[7];
	outPutMatrix.e[2]= t.e[0]*transPoseMatrix[8]+ t.e[1]*transPoseMatrix[9]+ 
					   t.e[2]*transPoseMatrix[10]+ t.e[3]*transPoseMatrix[11];
	outPutMatrix.e[3]= t.e[0]*transPoseMatrix[12]+ t.e[1]*transPoseMatrix[13]+ 
					   t.e[2]*transPoseMatrix[14]+ t.e[3]*transPoseMatrix[15];
	return outPutMatrix;
}
void matrix::transpose(){
	double transPoseMatrix [4*4];
	transPoseMatrix[0]=transformationMatrix[0];
	transPoseMatrix[1]=transformationMatrix[4];
	transPoseMatrix[2]=transformationMatrix[8];
	transPoseMatrix[3]=transformationMatrix[12];

	transPoseMatrix[4]=transformationMatrix[1];
	transPoseMatrix[5]=transformationMatrix[5];
	transPoseMatrix[6]=transformationMatrix[9];
	transPoseMatrix[7]=transformationMatrix[13];

	transPoseMatrix[8]=transformationMatrix[2];
	transPoseMatrix[9]=transformationMatrix[6];
	transPoseMatrix[10]=transformationMatrix[10];
	transPoseMatrix[11]=transformationMatrix[14];

	transPoseMatrix[12]=transformationMatrix[3];
	transPoseMatrix[13]=transformationMatrix[7];
	transPoseMatrix[14]=transformationMatrix[11];
	transPoseMatrix[15]=transformationMatrix[15];
	int j;
	for (j = 0; j < 4; j++){
		transformationMatrix[j*4]=transPoseMatrix[j*4];
		transformationMatrix[j*4+1]=transPoseMatrix[j*4+1];
		transformationMatrix[j*4+2]=transPoseMatrix[j*4+2];
		transformationMatrix[j*4+3]=transPoseMatrix[j*4+3];
    	}
	}

inline matrix translation(const tuple& t){
	matrix mout;
	mout.setIdentity();
	mout.transformationMatrix[3]=t.e[0];
	mout.transformationMatrix[7]=t.e[1];
	mout.transformationMatrix[11]=t.e[2];
	return mout;
}
inline matrix scale(const tuple& t){
	matrix mout;
	mout.setIdentity();
	mout.transformationMatrix[0]=t.e[0];
	mout.transformationMatrix[5]=t.e[1];
	mout.transformationMatrix[10]=t.e[2];
	return mout;
}
inline matrix rotatex(float angle){
	matrix mout;
	mout.setIdentity();
	mout.transformationMatrix[5]=cos(angle);
	mout.transformationMatrix[6]=-sin(angle);
	mout.transformationMatrix[9]=sin(angle);
	mout.transformationMatrix[10]=cos(angle);
	return mout;
}
inline matrix rotatey(float angle){
	matrix mout;
	mout.setIdentity();
	mout.transformationMatrix[0]=cos(angle);
	mout.transformationMatrix[2]=sin(angle);
	mout.transformationMatrix[8]=-sin(angle);
	mout.transformationMatrix[10]=cos(angle);
	return mout;
}
inline matrix rotatez(float angle){
	matrix mout;
	mout.setIdentity();
	mout.transformationMatrix[0]=cos(angle);
	mout.transformationMatrix[1]=-sin(angle);
	mout.transformationMatrix[4]=sin(angle);
	mout.transformationMatrix[5]=cos(angle);
	return mout;
}
inline matrix shearing(float& xy,float& xz, float& yx, float& yz, float& zx, float& zy){
	matrix mout;
	mout.transformationMatrix[0]=1;
	mout.transformationMatrix[1]=xy;
	mout.transformationMatrix[2]=xz;
	mout.transformationMatrix[3]=0;

	mout.transformationMatrix[4]=yx;
	mout.transformationMatrix[5]=1;
	mout.transformationMatrix[6]=yz;
	mout.transformationMatrix[7]=0;

	mout.transformationMatrix[8]=zx;
	mout.transformationMatrix[9]=zy;
	mout.transformationMatrix[10]=1;
	mout.transformationMatrix[11]=0;

	mout.transformationMatrix[12]=0;
	mout.transformationMatrix[13]=0;
	mout.transformationMatrix[14]=0;
	mout.transformationMatrix[15]=1;
	return mout;
}
inline matrix operator*(const matrix& m1, const matrix& m2){
	int i,j;
	matrix outPutMatrix;
	for (j=0;j<4;j++){
		outPutMatrix.transformationMatrix[j*4]= m1.transformationMatrix[j*4]*m2.transformationMatrix[0]+ 
												 m1.transformationMatrix[j*4+1]*m2.transformationMatrix[4]+ 
												 m1.transformationMatrix[j*4+2]*m2.transformationMatrix[8]+ 
												 m1.transformationMatrix[j*4+3]*m2.transformationMatrix[12];
		outPutMatrix.transformationMatrix[j*4+1]= m1.transformationMatrix[j*4]*m2.transformationMatrix[1]+ 
												 m1.transformationMatrix[j*4+1]*m2.transformationMatrix[5]+ 
												 m1.transformationMatrix[j*4+2]*m2.transformationMatrix[9]+ 
												 m1.transformationMatrix[j*4+3]*m2.transformationMatrix[13];
		outPutMatrix.transformationMatrix[j*4+2]= m1.transformationMatrix[j*4]*m2.transformationMatrix[2]+ 
												 m1.transformationMatrix[j*4+1]*m2.transformationMatrix[6]+ 
												 m1.transformationMatrix[j*4+2]*m2.transformationMatrix[10]+ 
												 m1.transformationMatrix[j*4+3]*m2.transformationMatrix[14];
		outPutMatrix.transformationMatrix[j*4+3]= m1.transformationMatrix[j*4]*m2.transformationMatrix[3]+ 
												 m1.transformationMatrix[j*4+1]*m2.transformationMatrix[7]+ 
												 m1.transformationMatrix[j*4+2]*m2.transformationMatrix[11]+ 
												 m1.transformationMatrix[j*4+3]*m2.transformationMatrix[15];
	}
	return outPutMatrix;
}
inline tuple operator*(const tuple& t,const matrix& m1){
	int i,j;
	tuple outPutMatrix;
	outPutMatrix.e[0]= t.e[0]*m1.transformationMatrix[0]+ t.e[1]*m1.transformationMatrix[1]+ 
					   t.e[2]*m1.transformationMatrix[2]+ t.e[3]*m1.transformationMatrix[3];
	outPutMatrix.e[1]= t.e[0]*m1.transformationMatrix[4]+ t.e[1]*m1.transformationMatrix[5]+ 
					   t.e[2]*m1.transformationMatrix[6]+ t.e[3]*m1.transformationMatrix[7];
	outPutMatrix.e[2]= t.e[0]*m1.transformationMatrix[8]+ t.e[1]*m1.transformationMatrix[9]+ 
					   t.e[2]*m1.transformationMatrix[10]+ t.e[3]*m1.transformationMatrix[11];
	outPutMatrix.e[3]= t.e[0]*m1.transformationMatrix[12]+ t.e[1]*m1.transformationMatrix[13]+ 
					   t.e[2]*m1.transformationMatrix[14]+ t.e[3]*m1.transformationMatrix[15];
	return outPutMatrix;
}

inline matrix invertMatrix(const matrix& m1){
    float det;
    int i,j;
	matrix m2;
    m2.transformationMatrix[0] =  m1.transformationMatrix[5] * m1.transformationMatrix[10] * m1.transformationMatrix[15] - 
                					 m1.transformationMatrix[5] * m1.transformationMatrix[11] * m1.transformationMatrix[14] - 
                					 m1.transformationMatrix[9] * m1.transformationMatrix[6] * m1.transformationMatrix[15] + 
                					 m1.transformationMatrix[9] * m1.transformationMatrix[7] * m1.transformationMatrix[14] +
                					 m1.transformationMatrix[13] * m1.transformationMatrix[6] * m1.transformationMatrix[11] - 
                					 m1.transformationMatrix[13] * m1.transformationMatrix[7] * m1.transformationMatrix[10];

    m2.transformationMatrix[1] = -m1.transformationMatrix[1] * m1.transformationMatrix[10] * m1.transformationMatrix[15] + 
                					 m1.transformationMatrix[1] * m1.transformationMatrix[11] * m1.transformationMatrix[14] + 
                					 m1.transformationMatrix[9] * m1.transformationMatrix[2] * m1.transformationMatrix[15] - 
                					 m1.transformationMatrix[9] * m1.transformationMatrix[3] * m1.transformationMatrix[14] - 
                					 m1.transformationMatrix[13] * m1.transformationMatrix[2] * m1.transformationMatrix[11] + 
                					 m1.transformationMatrix[13] * m1.transformationMatrix[3] * m1.transformationMatrix[10];

    m2.transformationMatrix[4] = -m1.transformationMatrix[4] * m1.transformationMatrix[10] * m1.transformationMatrix[15] + 
                					 m1.transformationMatrix[4] * m1.transformationMatrix[11] * m1.transformationMatrix[14] + 
                					 m1.transformationMatrix[8] * m1.transformationMatrix[6] * m1.transformationMatrix[15] - 
                					 m1.transformationMatrix[8] * m1.transformationMatrix[7] * m1.transformationMatrix[14] - 
                					 m1.transformationMatrix[12] * m1.transformationMatrix[6] * m1.transformationMatrix[11] + 
                					 m1.transformationMatrix[12] * m1.transformationMatrix[7] * m1.transformationMatrix[10];

    m2.transformationMatrix[8] =  m1.transformationMatrix[4] * m1.transformationMatrix[9] * m1.transformationMatrix[15] - 
                					 m1.transformationMatrix[4] * m1.transformationMatrix[11] * m1.transformationMatrix[13] - 
                					 m1.transformationMatrix[8] * m1.transformationMatrix[5] * m1.transformationMatrix[15] + 
                					 m1.transformationMatrix[8] * m1.transformationMatrix[7] * m1.transformationMatrix[13] + 
                					 m1.transformationMatrix[12] * m1.transformationMatrix[5] * m1.transformationMatrix[11] - 
                					 m1.transformationMatrix[12] * m1.transformationMatrix[7] * m1.transformationMatrix[9];

    m2.transformationMatrix[12] = -m1.transformationMatrix[4] * m1.transformationMatrix[9] * m1.transformationMatrix[14] + 
                					 m1.transformationMatrix[4] * m1.transformationMatrix[10] * m1.transformationMatrix[13] +
                					 m1.transformationMatrix[8] * m1.transformationMatrix[5] * m1.transformationMatrix[14] - 
                					 m1.transformationMatrix[8] * m1.transformationMatrix[6] * m1.transformationMatrix[13] - 
                					 m1.transformationMatrix[12] * m1.transformationMatrix[5] * m1.transformationMatrix[10] + 
                					 m1.transformationMatrix[12] * m1.transformationMatrix[6] * m1.transformationMatrix[9];



    m2.transformationMatrix[5] =  m1.transformationMatrix[0] * m1.transformationMatrix[10] * m1.transformationMatrix[15] - 
                					 m1.transformationMatrix[0] * m1.transformationMatrix[11] * m1.transformationMatrix[14] - 
                					 m1.transformationMatrix[8] * m1.transformationMatrix[2] * m1.transformationMatrix[15] + 
                					 m1.transformationMatrix[8] * m1.transformationMatrix[3] * m1.transformationMatrix[14] + 
                					 m1.transformationMatrix[12] * m1.transformationMatrix[2] * m1.transformationMatrix[11] - 
                					 m1.transformationMatrix[12] * m1.transformationMatrix[3] * m1.transformationMatrix[10];

    m2.transformationMatrix[9] = -m1.transformationMatrix[0] * m1.transformationMatrix[9] * m1.transformationMatrix[15] + 
                					 m1.transformationMatrix[0] * m1.transformationMatrix[11] * m1.transformationMatrix[13] + 
                					 m1.transformationMatrix[8] * m1.transformationMatrix[1] * m1.transformationMatrix[15] - 
                					 m1.transformationMatrix[8] * m1.transformationMatrix[3] * m1.transformationMatrix[13] - 
                					 m1.transformationMatrix[12] * m1.transformationMatrix[1] * m1.transformationMatrix[11] + 
                					 m1.transformationMatrix[12] * m1.transformationMatrix[3] * m1.transformationMatrix[9];

    m2.transformationMatrix[13] =  m1.transformationMatrix[0] * m1.transformationMatrix[9] * m1.transformationMatrix[14] - 
                					 m1.transformationMatrix[0] * m1.transformationMatrix[10] * m1.transformationMatrix[13] - 
                					 m1.transformationMatrix[8] * m1.transformationMatrix[1] * m1.transformationMatrix[14] + 
                					 m1.transformationMatrix[8] * m1.transformationMatrix[2] * m1.transformationMatrix[13] + 
                					 m1.transformationMatrix[12] * m1.transformationMatrix[1] * m1.transformationMatrix[10] - 
                					 m1.transformationMatrix[12] * m1.transformationMatrix[2] * m1.transformationMatrix[9];

    m2.transformationMatrix[2] =  m1.transformationMatrix[1] * m1.transformationMatrix[6] * m1.transformationMatrix[15] - 
                					 m1.transformationMatrix[1] * m1.transformationMatrix[7] * m1.transformationMatrix[14] - 
                					 m1.transformationMatrix[5] * m1.transformationMatrix[2] * m1.transformationMatrix[15] + 
                					 m1.transformationMatrix[5] * m1.transformationMatrix[3] * m1.transformationMatrix[14] + 
                					 m1.transformationMatrix[13] * m1.transformationMatrix[2] * m1.transformationMatrix[7] - 
                					 m1.transformationMatrix[13] * m1.transformationMatrix[3] * m1.transformationMatrix[6];
                					 
    m2.transformationMatrix[3] = -m1.transformationMatrix[1] * m1.transformationMatrix[6] * m1.transformationMatrix[11] + 
                 					 m1.transformationMatrix[1] * m1.transformationMatrix[7] * m1.transformationMatrix[10] + 
              						 m1.transformationMatrix[5] * m1.transformationMatrix[2] * m1.transformationMatrix[11] - 
              						 m1.transformationMatrix[5] * m1.transformationMatrix[3] * m1.transformationMatrix[10] - 
              						 m1.transformationMatrix[9] * m1.transformationMatrix[2] * m1.transformationMatrix[7] + 
              						 m1.transformationMatrix[9] * m1.transformationMatrix[3] * m1.transformationMatrix[6];


    m2.transformationMatrix[6] = -m1.transformationMatrix[0] * m1.transformationMatrix[6] * m1.transformationMatrix[15] + 
                					 m1.transformationMatrix[0] * m1.transformationMatrix[7] * m1.transformationMatrix[14] + 
                					 m1.transformationMatrix[4] * m1.transformationMatrix[2] * m1.transformationMatrix[15] - 
                					 m1.transformationMatrix[4] * m1.transformationMatrix[3] * m1.transformationMatrix[14] - 
                					 m1.transformationMatrix[12] * m1.transformationMatrix[2] * m1.transformationMatrix[7] + 
                					 m1.transformationMatrix[12] * m1.transformationMatrix[3] * m1.transformationMatrix[6];

    m2.transformationMatrix[10] =  m1.transformationMatrix[0] * m1.transformationMatrix[5] * m1.transformationMatrix[15] - 
                					 m1.transformationMatrix[0] * m1.transformationMatrix[7] * m1.transformationMatrix[13] - 
                					 m1.transformationMatrix[4] * m1.transformationMatrix[1] * m1.transformationMatrix[15] + 
                					 m1.transformationMatrix[4] * m1.transformationMatrix[3] * m1.transformationMatrix[13] + 
                					 m1.transformationMatrix[12] * m1.transformationMatrix[1] * m1.transformationMatrix[7] - 
                					 m1.transformationMatrix[12] * m1.transformationMatrix[3] * m1.transformationMatrix[5];

    m2.transformationMatrix[14] = -m1.transformationMatrix[0] * m1.transformationMatrix[5] * m1.transformationMatrix[14] + 
                					 m1.transformationMatrix[0] * m1.transformationMatrix[6] * m1.transformationMatrix[13] + 
                					 m1.transformationMatrix[4] * m1.transformationMatrix[1] * m1.transformationMatrix[14] - 
                					 m1.transformationMatrix[4] * m1.transformationMatrix[2] * m1.transformationMatrix[13] - 
                					 m1.transformationMatrix[12] * m1.transformationMatrix[1] * m1.transformationMatrix[6] + 
                					 m1.transformationMatrix[12] * m1.transformationMatrix[2] * m1.transformationMatrix[5];


    m2.transformationMatrix[7] =  m1.transformationMatrix[0] * m1.transformationMatrix[6] * m1.transformationMatrix[11] - 
                 					 m1.transformationMatrix[0] * m1.transformationMatrix[7] * m1.transformationMatrix[10] - 
                 					 m1.transformationMatrix[4] * m1.transformationMatrix[2] * m1.transformationMatrix[11] + 
                 					 m1.transformationMatrix[4] * m1.transformationMatrix[3] * m1.transformationMatrix[10] + 
                 					 m1.transformationMatrix[8] * m1.transformationMatrix[2] * m1.transformationMatrix[7] - 
                 					 m1.transformationMatrix[8] * m1.transformationMatrix[3] * m1.transformationMatrix[6];

    m2.transformationMatrix[11] = -m1.transformationMatrix[0] * m1.transformationMatrix[5] * m1.transformationMatrix[11] + 
                 					 m1.transformationMatrix[0] * m1.transformationMatrix[7] * m1.transformationMatrix[9] + 
                 					 m1.transformationMatrix[4] * m1.transformationMatrix[1] * m1.transformationMatrix[11] - 
                 					 m1.transformationMatrix[4] * m1.transformationMatrix[3] * m1.transformationMatrix[9] - 
                 					 m1.transformationMatrix[8] * m1.transformationMatrix[1] * m1.transformationMatrix[7] + 
                 					 m1.transformationMatrix[8] * m1.transformationMatrix[3] * m1.transformationMatrix[5];

    m2.transformationMatrix[15] =  m1.transformationMatrix[0] * m1.transformationMatrix[5] * m1.transformationMatrix[10] - 
                 					 m1.transformationMatrix[0] * m1.transformationMatrix[6] * m1.transformationMatrix[9] - 
                 					 m1.transformationMatrix[4] * m1.transformationMatrix[1] * m1.transformationMatrix[10] + 
                 					 m1.transformationMatrix[4] * m1.transformationMatrix[2] * m1.transformationMatrix[9] + 
               						 m1.transformationMatrix[8] * m1.transformationMatrix[1] * m1.transformationMatrix[6] - 
                 					 m1.transformationMatrix[8] * m1.transformationMatrix[2] * m1.transformationMatrix[5];

    det = m1.transformationMatrix[0] * m2.transformationMatrix[0] + 
    	  m1.transformationMatrix[1] * m2.transformationMatrix[4] + 
    	  m1.transformationMatrix[2] * m2.transformationMatrix[8] + 
    	  m1.transformationMatrix[3] * m2.transformationMatrix[12];

    if (det == 0){
    	std::cout << "Error Determinant 0\n";
    	exit (EXIT_FAILURE);
    }

    det = 1.0 / det;

    for (j = 0; j < 4; j++){
    	for (i = 0; i < 4; i++){
        	m2.transformationMatrix[j*4+i] = m2.transformationMatrix[j*4+i] * det;
        }
    }
    return m2;
}
#endif