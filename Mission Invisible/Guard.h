#pragma once

#include "DynamicObject.h"
#include <vector>
#include <memory>

class Thief;
class GuardFactory;

// a base class to guard

class Guard : public DynamicObject
{
public:
	virtual void setMove(std::string &&moves) = 0; // to get how the guard will move
	virtual void collideWith(Thief &obj) = 0;
	virtual void collideWith(const Guard &obj) = 0;

	virtual bool isShootArrow() = 0; // return if shoot arrow or not
									 // if shoot arrow return start value and move vector
	virtual std::pair<sf::Vector2f, sf::Vector2f> getArrowData() = 0; 


protected:
	template <typename T>
	static bool registerInGuardFactory(const std::string &objName);

};

template<typename T>
inline bool Guard::registerInGuardFactory(const std::string & objName)
{
	return  GuardFactory::getInstace().registerObj(objName, [](const int&x, const int&y) -> std::shared_ptr<Guard> { return std::make_shared<T>(x, y); });
}