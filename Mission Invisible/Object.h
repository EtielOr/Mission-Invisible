#pragma once

#include <SFML/Graphics.hpp>
#include "Const.h"
#include "ResourceManeger.h"

// base class to drawable objects

class MapObject;
class Wall;
class Floor;
class Door;
class Treasure;
class DynamicObject;



class Object : public sf::Drawable
{
public:
	virtual void collideWith(DynamicObject&) = 0; // for doble dispacth
	virtual void collideWith(const Wall&) = 0;
	virtual void collideWith(const Floor&) = 0;
	virtual void collideWith(Door&) = 0;
	virtual void collideWith(const Treasure&) = 0;

	virtual sf::FloatRect getGlobalBounds()  const = 0 ; // return Sprite bounds
	virtual sf::Vector2f getPosition() const = 0;  // return Sprite pos
	virtual void loadTexture(const std::string &name) = 0 ; // get what texture to load and load it




	virtual ~Object() {};
protected:
	sf::Sprite m_sprite;
	// virtual void draw(sf::RenderTarget& target, sf::RenderStates states) =0 form sf::Drawable

};

