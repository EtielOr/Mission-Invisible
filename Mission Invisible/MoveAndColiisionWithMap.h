#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include "Collision.h"
#include "Const.h"

class DynamicObject;
class Wall;
class Door;
class mapViewPass;


// class that move dynamicobject and make collsion with the map

class MoveAndColiisionWithMap
{
public:
	MoveAndColiisionWithMap(sf::Sprite & sprite,DynamicObject &coliider) : m_Rsprite(sprite), m_coliider(coliider){};

	void collideWith(const Wall&obj);
	void collideWith(const Door &obj);

	// move the object, get the sprite, moveDelta, and the objects on the map
	void move(const sf::Vector2f& moveDelta, const mapViewPass& mapObj);

private:
	sf::Vector2f lastMove; // the last postion
	DynamicObject & m_coliider; // the object the collied
	sf::Sprite & m_Rsprite;


	inline sf::Vector2i getBoardLocation() const; // calcaute sprite place on the board
	void testCollosion(const mapViewPass& mapObj); // testCollosion
	void moveBack(const sf::FloatRect &from); // moveBack to not colied
};



inline sf::Vector2i MoveAndColiisionWithMap::getBoardLocation() const
{
	return sf::Vector2i(int(m_Rsprite.getPosition().x / TILESIZE), int(m_Rsprite.getPosition().y / TILESIZE));
}
