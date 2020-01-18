#include "Floor.h"
#include "ObjectFactory.h"


bool Floor::isRegisterFactory = registerInMapFactory<Floor>(1,10); // register on the factory



Floor::Floor(const int & x, const int & y)
{
	m_sprite.setPosition(float(x)*TILESIZE, float(y)*TILESIZE);
}


bool Floor::openDoor(Door & obj)
{
	return false;
}

bool Floor::openDoor(Key & obj)
{
	return false;
}

bool Floor::openDoor(std::shared_ptr<Items>& obj)
{
	return false;
}

bool Floor::isPassAble()
{
	return true;
}

void Floor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	 target.draw(m_sprite);
}

sf::FloatRect Floor::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f Floor::getPosition() const
{
	return m_sprite.getPosition();
}

void Floor::loadTexture(const std::string & name)
{
	// get the texture
	m_sprite.setTexture(ResourceManeger::getInstance().getTexture(name));

	// get the texture pos on the texture
	m_sprite.setTextureRect(ResourceManeger::getInstance().getTexturePos(name));

}