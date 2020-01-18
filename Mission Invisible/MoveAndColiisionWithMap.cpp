#include "MoveAndColiisionWithMap.h"
#include "LevelMap.h"
#include "Wall.h"
#include "Door.h"

void MoveAndColiisionWithMap::collideWith(const Door &obj)
{
	if (Collision::MapObjectAndDynamicObject(obj, m_Rsprite))
		moveBack(obj.getGlobalBounds());
}

void MoveAndColiisionWithMap::collideWith(const Wall&obj)
{
	if (Collision::MapObjectAndDynamicObject(obj, m_Rsprite))
		moveBack(obj.getGlobalBounds());
}

void MoveAndColiisionWithMap::move(const sf::Vector2f & moveDelta, const mapViewPass& mapObj)
{
	static const sf::Vector2f zeroVector(0, 0); // to test if didn't move

	sf::Vector2f moveX(moveDelta.x, 0); // to move on x then on y
	sf::Vector2f moveY(0, moveDelta.y);

	if (moveX != zeroVector) // move on x
	{
		m_Rsprite.move(moveX);
		lastMove = moveX;
		testCollosion(mapObj);
	}

	if (moveY != zeroVector) // move on y
	{
		m_Rsprite.move(moveY);
		lastMove = moveY;
		testCollosion(mapObj);
	}



}


void MoveAndColiisionWithMap::testCollosion(const mapViewPass& mapObj)
{
	sf::Vector2i spritePos = getBoardLocation(); // get the place on the board

	auto map = mapObj.pass();

	static const std::array<sf::Vector2i, 4> collisionCheck // test on 4 place collision
						= { sf::Vector2i(0, 0),
							sf::Vector2i(1, 0),
							sf::Vector2i(0, 1),
							sf::Vector2i(1, 1) };

	for (size_t i = 0; i < collisionCheck.size(); i++) // test the collison
	{
		sf::Vector2i checkPoint = spritePos + collisionCheck[i];

		if (checkPoint.y < 0 || checkPoint.y >= int(map.size()) ||
			checkPoint.x < 0 || checkPoint.x >= int(map[checkPoint.y].size()))
			continue;

		map[checkPoint.y][checkPoint.x]->collideWith(m_coliider);
	}
}

void MoveAndColiisionWithMap::moveBack(const sf::FloatRect &from)
{
	 m_Rsprite.move(-lastMove); // undo the move

	if (lastMove.y < 0) // move up last time
		m_Rsprite.setPosition(m_Rsprite.getPosition().x, from.top + TILESIZE);
	else if (lastMove.y > 0) // move down last time
		m_Rsprite.setPosition(m_Rsprite.getPosition().x, from.top - TILESIZE);
	if (lastMove.x < 0) // move left last time
		m_Rsprite.setPosition(from.left + TILESIZE, m_Rsprite.getPosition().y);
	else if (lastMove.x > 0) // move right last time
		m_Rsprite.setPosition(from.left - TILESIZE, m_Rsprite.getPosition().y);
}
