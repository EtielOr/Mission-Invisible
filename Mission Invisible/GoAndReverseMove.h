#pragma once

#include <vector>
#include "Const.h"
#include "MoveLogic.h"

// a move logic when moveing back and foawrd form a point

class GoAndReverseMove : public MoveLogic
{
public:
	GoAndReverseMove(std::vector<MOVE_POS> &&movelist);

	virtual sf::Vector2f getMove(const float &speed);
	virtual MOVE_POS getLastPos();


protected:
	bool moveInReverst; // how if move is reverst or not
	int currPos; // currPos in the vector
	int currMoves; // how many moves made
	int moveToMake; // how many move to make base the speed
	sf::Vector2f currMovePos; // the curr move pos
	std::vector<MOVE_POS> m_direction;


	void setMoveVector();
	void setMoveVectorReverst();

};
