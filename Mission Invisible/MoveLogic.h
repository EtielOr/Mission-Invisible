#pragma once

#include <SFML\Graphics.hpp>
#include "Const.h"

// base class to how dynamic object move

class MoveLogic
{
public:
	virtual sf::Vector2f getMove(const float &speed) = 0;
	virtual MOVE_POS getLastPos() = 0; // return the last pas

protected:
	MOVE_POS lastPos;
};