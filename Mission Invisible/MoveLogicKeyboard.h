#pragma once

#include "MoveLogic.h"

class MoveLogicKeyboard : public MoveLogic
{
public:
	virtual sf::Vector2f getMove(const float &speed);
	virtual MOVE_POS getLastPos();
};