#include "Door.h"
#include "ObjectFactory.h"
#include "MoveAndColiisionWithMap.h"


bool Door::isRegisterFactory = registerInMapFactory<Door>(51,52); // register on the factory

Door::Door(const int & x, const int & y) : isOpen(false)
{
	m_sprite.setPosition(float(x)*TILESIZE, float(y)*TILESIZE);
}

void Door::collideWith(DynamicObject & obj)
{
	if (!isOpen)
		obj.collideWith(*this);
}

bool Door::openDoor(Door & obj)
{
	return false;
}

bool Door::openDoor(Key & obj)
{
	if (isOpen) // you can't open opened door
		return false;

	isOpen = true;
	m_sprite.setTextureRect(ResourceManeger::getInstance().getTexturePos("53"));
	// m_sprite.setColor(sf::Color(80, 80, 80, 100));
	return true;
}

bool Door::openDoor(std::shared_ptr<Items>& obj)
{
	return false;
}


bool Door::isPassAble()
{
	return isOpen;
}

void Door::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

sf::FloatRect Door::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f Door::getPosition() const
{
	return m_sprite.getPosition();
}

void Door::loadTexture(const std::string & name)
{
	// get the texture
	m_sprite.setTexture(ResourceManeger::getInstance().getTexture(name));

	// get the texture pos on the texture
	m_sprite.setTextureRect(ResourceManeger::getInstance().getTexturePos(name));

}