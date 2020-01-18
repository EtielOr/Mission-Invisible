#pragma once

#include "MoveLogic.h"

// a move logic when going back and fort

class CircularMove : public MoveLogic
{
public:
	CircularMove(std::vector<MOVE_POS> &&movelist);

	virtual sf::Vector2f getMove(const float &speed); 
	virtual MOVE_POS getLastPos();


protected:
	int currPos; // currPos in the vector
	int currMoves; // how many moves made
	int moveToMake; // how many move to make base the speed
	sf::Vector2f currMovePos; // the curr move pos
	std::vector<MOVE_POS> m_direction;

};

