#pragma once

#include "StaticObject.h"
class MapObjectFactory;

// base class to MapObjects

class  MapObject : public StaticObject
{
public:
	virtual ~MapObject() {};

	virtual bool isPassAble() = 0; // to map sceach algortihom


protected:

	template <typename T>
	static bool registerInMapFactory(const int & startNum, const int &endNum); // register Object in his map factory

};


template<typename T>
inline bool MapObject::registerInMapFactory(const int & startNum,const int &endNum)
{
	for (int i = startNum; i <= endNum; i++)
	{
		MapObjectFactory::getInstace().registerObj(std::to_string(i), [](const int&x, const int&y) -> std::shared_ptr<MapObject> { return std::make_shared<T>(x, y); });
	}
	return true;
}
