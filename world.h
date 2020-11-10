#ifndef WORLD
#define WORLD
#include <iostream>
#include <list>
#include <vector>
#include "sphere.h"
#include "matrix.h"
#include "tuple.h"
#include "light.h"
#include "shape.h"


class world {
public:
	world(){}
	shape** objectsInWorld;//TODO add other data types 
	void addObject(shape* newObject, int position);
	void setViewTransform(const tuple& from, const tuple& to, const tuple& up);
	void createWorldList(int& TotalObjects);
	light sourceLight;
};
void world::createWorldList(int& TotalObjects){
	objectsInWorld = (shape**)malloc(TotalObjects*sizeof(shape*));
}
void world::addObject(shape* newObject, int position){
	objectsInWorld[position]= newObject;
}

#endif 