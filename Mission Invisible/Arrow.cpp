#include "Arrow.h"
#include "Collision.h"
#include "Wall.h"
#include "Door.h"
#include "Thief.h"
#include "CommandMap.h"

const double ARROW_TEXTURE_ROTATION = 135.0; // the rotation of the texture
const float ARROW_SPEED = 2.1f;

Arrow::Arrow(sf::Vector2f startPos, sf::Vector2f moveVect)
	: moveDirection(moveVect*ARROW_SPEED), arrowEnd(false),hitingPoint(ARROW_HIT_SIZE),
	moveColiison(std::make_unique<MoveAndColiisionWithMap>(m_sprite, *this))
{
	m_sprite.setOrigin(TILESIZE / 2, TILESIZE / 2);
	m_sprite.setPosition(startPos);


	m_sprite.setRotation(static_cast<float>(calcRotationDeg()));
	hitingPoint.setOrigin(static_cast<float>(ARROW_HIT_SIZE / 2), static_cast<float>(ARROW_HIT_SIZE / 2));
	hitingPoint.setPosition(startPos); // in the arrow point
	hitingPoint.move(moveVect * static_cast<float>(TILESIZE/2)); // move to the end of the arrow

}

void Arrow::update(mapViewPass & mapObj)
{
	moveColiison->move(moveDirection, mapObj); // move the arrow
	hitingPoint.move(moveDirection);
}


void Arrow::collideWith(DynamicObject & obj)
{

}

void Arrow::collideWith(const Wall & obj)
{
	if (Collision::ArrowAndObject(obj, hitingPoint))
	{
		m_sprite.setColor(sf::Color::Red);
		arrowEnd = true;
	}
}

void Arrow::collideWith(Door & obj)
{
	if (Collision::ArrowAndObject(obj, hitingPoint))
	{
		m_sprite.setColor(sf::Color::Red);
		arrowEnd = true;
	}
}

void Arrow::collideWith(Thief & obj)
{

	if (Collision::ArrowAndObject(obj, hitingPoint))
	{
		ResourceManeger::getInstance().getSound(DEAD_SD).play();
		ResourceManeger::getInstance().getSound(DEAD_SD).setLoop(false);
		ResourceManeger::getInstance().getSound(DEAD_SD).setVolume(100.f);
		CommandMap::getInstace().doCommand(RESTART_LEVEL_CMD);
	}
}





double Arrow::calcRotationDeg()
{


	double deg;

	if (moveDirection.y > 0 && moveDirection.x == 0) // to not atan( y/0)
		deg = 90;
	else if (moveDirection.y < 0 && moveDirection.x == 0)
		deg = 270; 
	else
	{
		deg = std::atan((moveDirection.y / moveDirection.x));

		deg *= 180 / M_PI;

		if (moveDirection.y > 0 && moveDirection.x < 0)
			deg += 180; // to fix atan return value
		else if (moveDirection.y < 0 && moveDirection.x < 0)
			deg += 180; // to fix atan return value
		else  if (moveDirection.y < 0 && moveDirection.x > 0)
			deg +=360;
	}


	if (deg > ARROW_TEXTURE_ROTATION) // to fix texture rotation
		deg -=  ARROW_TEXTURE_ROTATION; // to fix texture rotation
	else if( deg < ARROW_TEXTURE_ROTATION)
		deg += (360 - ARROW_TEXTURE_ROTATION);



	return deg;
}

void Arrow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}


sf::FloatRect Arrow::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f Arrow::getPosition() const
{
	return m_sprite.getPosition();
}

void Arrow::loadTexture(const std::string & name)
{
	// get the texture
	m_sprite.setTexture(ResourceManeger::getInstance().getTexture(name));

	// get the texture pos on the texture
	m_sprite.setTextureRect(ResourceManeger::getInstance().getTexturePos(name));

}