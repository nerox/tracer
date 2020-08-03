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
	std::list<shape*> objectsInWorld;//TODO add other data types 
	void addObject(shape* newObject);
	void setViewTransform(const tuple& from, const tuple& to, const tuple& up);
	int getWorldSize();
	bool isPointShadow(const tuple inputPoint);
	light sourceLight;

};

void world::addObject(shape* newObject){
	objectsInWorld.push_back (newObject);
}

int world::getWorldSize(){
	return objectsInWorld.size();
}

#endif 