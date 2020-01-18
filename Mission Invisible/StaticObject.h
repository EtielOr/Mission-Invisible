#pragma once
#include "Object.h"
#include <memory>

class Items;
class MapObject;
class Key;
class Door;

// base class to StaticObjects



class StaticObject : public Object
{
public:
	virtual bool openDoor(Door& obj) = 0;
	virtual bool openDoor(Key& obj) = 0;
	virtual bool openDoor(std::shared_ptr<Items>& obj) = 0;


	virtual ~StaticObject() {};

};



