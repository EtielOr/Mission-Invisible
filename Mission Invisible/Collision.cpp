#include "Collision.h"
#include "MapObject.h"
#include "DynamicObject.h"
#include "Thief.h"
#include "Guard.h"
#include "Items.h"


bool Collision::MapObjectAndDynamicObject(const MapObject & obj1, const sf::Sprite& obj2)
{
	sf::FloatRect mapObj = obj1.getGlobalBounds(); // 2 box test
	sf::FloatRect DynamObj = obj2.getGlobalBounds();

	if (mapObj.left < (DynamObj.left + DynamObj.width) - 2 && mapObj.top < (DynamObj.top + DynamObj.height) - 2 &&
		DynamObj.left < (mapObj.left + mapObj.width) - 2 && DynamObj.top < (mapObj.top + mapObj.height) - 2)
		return true;
	else
		return false;
}

bool Collision::ThiefAndHeradCircle(const Thief &thief, const sf::CircleShape& m_circle)
{

	double collideDis = static_cast<double>((m_circle.getRadius() + TILESIZE / 2));
	return collison2Circles<Thief, sf::CircleShape>(thief, m_circle, collideDis);

}

bool Collision::ThiefAndGuard(const Thief & thief, const Guard & guard)
{
	return collison2Circles<Thief, Guard>(thief, guard, TILESIZE);
}

bool Collision::ThifeAndItems(const Thief &thief, const Items & obj2)
{
	return collison2Circles<Thief, Items>(thief, obj2, TILESIZE);
}

bool Collision::ArrowAndObject(const Object &obj, const sf::CircleShape& m_circle)
{
	double collideDis = static_cast<double>((m_circle.getRadius() + TILESIZE / 2));
	return collison2Circles<Object, sf::CircleShape>(obj, m_circle, collideDis);
}

