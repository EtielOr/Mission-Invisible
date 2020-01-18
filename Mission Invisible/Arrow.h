#pragma once

#define _USE_MATH_DEFINES// for M_PI
#include <cmath>

#include "DynamicObject.h"
#include "MoveAndColiisionWithMap.h"
#include <memory>

class mapViewPass;
class Thief;
class Guard;

const float ARROW_HIT_SIZE = 3.f;

class Arrow : public DynamicObject
{
public:
	Arrow(sf::Vector2f startPos, sf::Vector2f moveVect);

	virtual void update(mapViewPass& mapObj); // move the guard

	virtual void collideWith(DynamicObject&obj);
	virtual void collideWith(const Wall&obj);
	virtual void collideWith(Door&obj);
	virtual void collideWith(const Floor&) {};
	virtual void collideWith(Thief &obj);
	virtual void collideWith(const Treasure&) {};

	virtual void collideWith(const Guard &obj) {};


	inline bool isEnded(); // if the arrow end

	virtual sf::FloatRect getGlobalBounds()  const; // return Sprite bounds
	virtual sf::Vector2f getPosition() const;  // return Sprite pos

	virtual void loadTexture(const std::string &name); // get what texture to load and load it





private:
	sf::Vector2f moveDirection; // the Direction the arrow move
	sf::CircleShape hitingPoint; // where the arrow hit for colliditon
	std::unique_ptr<MoveAndColiisionWithMap> moveColiison; // to move and collied

	bool arrowEnd; // if the arrow ended or not

	double calcRotationDeg(); // calc the Rotation deg by the move direction

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // to draw the map
};

inline bool Arrow::isEnded()
{
	return arrowEnd;
}


