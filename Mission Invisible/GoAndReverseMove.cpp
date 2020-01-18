#include "GoAndReverseMove.h"

GoAndReverseMove::GoAndReverseMove(std::vector<MOVE_POS>&& movelist)
	: currPos(0), moveInReverst(false), currMoves(0), m_direction(std::move(movelist)), moveToMake(0)
{
}

sf::Vector2f GoAndReverseMove::getMove(const float&speed)
{
	if (currMoves < moveToMake) // when in move don't make new speed
	{
		currMoves++;
		return currMovePos;
	}
	else
	{
		if (moveInReverst)  // when fin move get to the next move
			--currPos;
		else
			++currPos;

		if (currPos < 0 || currPos >= int(m_direction.size())) // the next  pos
		{
			moveInReverst = !moveInReverst; // when to get backword or fowarsd

			if (moveInReverst)  // when fin move get to the next move
				--currPos;
			else
				++currPos;
		}

		currMoves = 0; // reset curr move
	}


	currMovePos = sf::Vector2f(0, 0); // make new vector a Zero

	if (moveInReverst)
		setMoveVectorReverst();
	else
		setMoveVector();


	currMovePos *= speed; // add speed

	moveToMake = static_cast<int>(TILESIZE / (BASE_SPEED * speed)); // how many move need to make


	currMoves++; // make move
	return currMovePos; // return the next pos

}

MOVE_POS GoAndReverseMove::getLastPos()
{
	return lastPos;
}

void GoAndReverseMove::setMoveVector()
{
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
}

void GoAndReverseMove::setMoveVectorReverst()
{
	switch (m_direction[currPos])
	{
	case UP_CM:
		currMovePos += sf::Vector2f(0, BASE_SPEED);
		lastPos = DOWN_CM;
		break;
	case  DOWN_CM:
		currMovePos += sf::Vector2f(0, -BASE_SPEED);
		lastPos = UP_CM;
		break;
	case LEFT_CM:
		currMovePos += sf::Vector2f(BASE_SPEED, 0);
		lastPos = RIGHT_CM;
		break;
	case RIGHT_CM:
		currMovePos += sf::Vector2f(-BASE_SPEED, 0);
		lastPos = LEFT_CM;
		break;
	default:
		lastPos = m_direction[currPos];
		break;
	}

}
