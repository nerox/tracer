#ifndef HITLIST
#define HITLIST
#include <iostream>
#include <list>
#include <vector>
#include "material.h"
#include "shape.h"
struct ObjectHit
{
     double hitPoint;
     material hitObjectMaterial;
     shape* shapeAdress;
};
bool operator<(ObjectHit const & first, ObjectHit const & second)
{
	return first.hitPoint < second.hitPoint;
}
class hitList {
public:
	hitList(){}
	~hitList();
    void flushHitList();
    void hitListSort();
    int gethitListSize();
    void addHit(double &inputHitPoint, material& materialHitObject, shape* shapeObjectHit);
	std::list<ObjectHit> localHitList;//TODO add other data types 
};
hitList::~hitList() 
{ 
	//TODO run memory leaks
	localHitList.clear();
} 

int hitList::gethitListSize(){
	return localHitList.size();
}
void hitList::flushHitList(){
	localHitList.clear();
}

void hitList::addHit(double &inputHitPoint, material& materialHitObject, shape* shapeObjectHit){
	ObjectHit insertObject = {inputHitPoint ,materialHitObject,shapeObjectHit};
	localHitList.push_back(insertObject);
}
void hitList::hitListSort(){
	localHitList.sort();
}
	
#endif

