#pragma once

#include "StaticObject.h"

class Thief;
class Key;
class HeardlessPotion;
class mapViewPass;
class ItemFactory;

class Items : public StaticObject
{
public:
	virtual bool collideItem(const Thief& obj) = 0;

	virtual bool usedItem(Thief& obj, mapViewPass& mapObj) = 0; // to used item
	virtual void setPosition(float x, float y) = 0; // set the sprite in new position

protected:

	template <typename T>
	static bool registerInItemsFactory(const std::string &objName);
};



template<typename T>
inline bool Items::registerInItemsFactory(const std::string & objName)
{
	return  ItemFactory::getInstace().registerObj(objName, [](const int&x, const int&y) -> std::shared_ptr<Items> { return std::make_unique<T>(x, y); });
}
