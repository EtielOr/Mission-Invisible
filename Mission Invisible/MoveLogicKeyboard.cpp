#include "MoveLogicKeyboard.h"

sf::Vector2f MoveLogicKeyboard::getMove(const float &speed)
{
	sf::Vector2f moveTo;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		moveTo += sf::Vector2f(0, -BASE_SPEED);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		moveTo += sf::Vector2f(0, BASE_SPEED);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		moveTo += sf::Vector2f(-BASE_SPEED, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		moveTo += sf::Vector2f(BASE_SPEED, 0);


	return moveTo*speed;
}

MOVE_POS MoveLogicKeyboard::getLastPos()
{
	return UP_CM;
}
