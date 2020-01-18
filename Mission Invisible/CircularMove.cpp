#include "CircularMove.h"



CircularMove::CircularMove(std::vector<MOVE_POS>&& movelist)
	: currPos(0), currMoves(0), m_direction(std::move(movelist)),
	moveToMake(0)
{
}

sf::Vector2f CircularMove::getMove(const float&speed)
{
	if (currMoves < moveToMake) // when in move don't make new speed
	{
		currMoves++;
		return currMovePos;
	}
	else
	{
		++currPos; // when fin move get to the next move
		currMoves = 0; // reset curr move

		if (currPos >= int(m_direction.size())) // when curr pos outsdie the vector
			currPos = 0; 
	}


	currMovePos = sf::Vector2f(0, 0); // make new vector a Zero

	switch (m_direction[currPos])
	{
	case UP_CM:
		currMovePos += sf::Vector2f(0, -BASE_SPEED);
		break;
	case  DOWN_CM:
		currMovePos += sf::Vector2f(0, BASE_SPEED);
		break;
	case LEFT_CM:
		currMovePos += sf::Vector2f(-BASE_SPEED, 0);
		break;
	case RIGHT_CM:
		currMovePos += sf::Vector2f(BASE_SPEED, 0);
		break;
	default:
		break;
	}
	lastPos = m_direction[currPos];
	currMovePos *= speed; // add speed

	
	moveToMake = static_cast<int>(TILESIZE / (BASE_SPEED * speed) ); // how many move need to make


	currMoves++; // make move
	return currMovePos; // return the next pos

}

MOVE_POS CircularMove::getLastPos()
{
	return lastPos;
}
