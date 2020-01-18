#pragma once

#define _USE_MATH_DEFINES// for M_PI
#include <cmath>

#include "Guard.h"
#include "MoveAndColiisionWithMap.h"
#include <sstream>

#include "CircularMove.h"
#include "GoAndReverseMove.h"





class SeeGuard : public Guard
{
public:
	SeeGuard(const int &x, const int &y);
	virtual void update(mapViewPass& mapObj); // move the guard
	virtual void setMove(std::string &&moves); // get sting to how to move


	virtual void collideWith(DynamicObject&obj);
	virtual void collideWith(const Wall&obj);
	virtual void collideWith(Door&obj);
	virtual void collideWith(const Floor&) {};
	virtual void collideWith(Thief &obj);
	virtual void collideWith(const Treasure&) {};

	virtual void collideWith(const Guard &obj) {};


	virtual sf::FloatRect getGlobalBounds()  const; // return Sprite bounds
	virtual sf::Vector2f getPosition() const;  // return Sprite pos

	virtual void loadTexture(const std::string &name); // get what texture to load and load it




private:
	sf::VertexArray m_see; // circle of hearing raudis

	std::unique_ptr<MoveAndColiisionWithMap> moveColiison; // to move and collied

	std::unique_ptr<MoveLogic> m_moveTo; //the move logic of the guard

	float seeRangeFactor; // the factor of see range

	virtual bool isShootArrow(); // return if shoot arrow or not
								 // if shoot arrow return start value and move vector
	virtual std::pair<sf::Vector2f, sf::Vector2f> getArrowData();


	sf::Clock updateTime; // to not update see every frame 
	sf::Clock arrowShootTimer; // the tile form arrow to arrow
	bool thiefIsIn;
	bool shootArrow;
	
	GUARD_STATS stauts; // if the guard stating or moving

	sf::Vector2f arrowShootStart; // the data when shoot the arrow
	sf::Vector2f arrowShootMove;

	void updataSee(mapViewPass& mapObj); // update guard see
	int getStartDeg();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // to draw the map
	static bool isRegisterFactory; // to register in the factor


};