#pragma once

#include "Object.h"

// asbtract class for dynamic objects

class mapViewPass;

class DynamicObject : public Object
{
public:
	DynamicObject() : speed(1.f) {};
	virtual void update(mapViewPass& mapObj) = 0; // update the object


	virtual ~DynamicObject() {}; 
protected:
	float speed;
};
