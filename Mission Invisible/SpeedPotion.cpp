#include "SpeedPotion.h"
#include "Key.h"
#include "ObjectFactory.h"
#include "Door.h"
#include "Thief.h"
#include "LevelMap.h"

bool SpeedPotion::isRegisterFactory = registerInItemsFactory<SpeedPotion>("SpeedPotion"); // register on the factory


SpeedPotion::SpeedPotion(const int & x, const int & y)
{
	m_sprite.setPosition(float(x)*TILESIZE, float(y)*TILESIZE);
}

bool SpeedPotion::collideItem(const Thief& obj)
{
	return Collision::ThifeAndItems(obj, *this);
}


bool SpeedPotion::openDoor(Door & obj)
{
	return false;
}

bool SpeedPotion::openDoor(Key & obj)
{
	return false;
}

bool SpeedPotion::openDoor(std::shared_ptr<Items>& obj)
{
	return false;
}

bool SpeedPotion::usedItem(Thief & obj, mapViewPass& mapObj)
{
	return obj.usedItem(*this, mapObj);
}


void SpeedPotion::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

sf::FloatRect SpeedPotion::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f SpeedPotion::getPosition() const
{
	return m_sprite.getPosition();
}

void SpeedPotion::loadTexture(const std::string & name)
{
	// get the texture
	m_sprite.setTexture(ResourceManeger::getInstance().getTexture(name));

	// get the texture pos on the texture
	m_sprite.setTextureRect(ResourceManeger::getInstance().getTexturePos(name));

}



void SpeedPotion::setPosition(float x, float y)
{
	m_sprite.setPosition(x, y);
}