#pragma once

#include <SFML/Graphics.hpp>

class MapObject;
class DynamicObject;
class Thief;
class Items;
class Guard;
class Object;
class Arrow;


// class to calc if there collisoon



namespace Collision
{
	bool MapObjectAndDynamicObject(const MapObject &obj, const sf::Sprite &obj2);
	bool ThiefAndHeradCircle(const Thief &thief, const sf::CircleShape& m_circle);
	bool ThiefAndGuard(const Thief &thief,const Guard &guard);
	bool ThifeAndItems(const Thief &thief, const Items &obj2);
	bool ArrowAndObject(const Object &obj, const sf::CircleShape& m_circle);

	inline double Distance(const sf::Vector2f & v1, const sf::Vector2f & v2); // calacue distance

	template<typename T1, typename T2>
		bool collison2Circles(const T1& t1obj, const T2&t2obj, const double& smallerThen);
};

double Collision::Distance(const sf::Vector2f & v1, const sf::Vector2f & v2)
{
	return  std::sqrt((v1.x - v2.x)*(v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y));
}


template<typename T1, typename T2>
  bool Collision::collison2Circles(const T1 & t1obj, const T2& t2obj, const double& smallerThen)
{
	sf::FloatRect obj1 = t1obj.getGlobalBounds(); // 2 circle test
	sf::FloatRect obj2 = t2obj.getGlobalBounds();

	sf::Vector2f v1(obj1.left + obj1.width / 2, obj1.top + obj1.height / 2);
	sf::Vector2f v2(obj2.left + obj2.width / 2, obj2.top + obj2.height / 2);


	return (Distance(v1, v2) <= smallerThen);
}