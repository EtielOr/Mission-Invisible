#include "HeardlessPotion.h"
#include "Key.h"
#include "ObjectFactory.h"
#include "Door.h"
#include "Thief.h"
#include "LevelMap.h"

bool HeardlessPotion::isRegisterFactory = registerInItemsFactory<HeardlessPotion>("HeardlessPotion"); // register on the factory


HeardlessPotion::HeardlessPotion(const int & x, const int & y)
{
	m_sprite.setPosition(float(x)*TILESIZE, float(y)*TILESIZE);
}

bool HeardlessPotion::collideItem(const Thief& obj)
{
	return Collision::ThifeAndItems(obj, *this);
}


bool HeardlessPotion::openDoor(Door & obj)
{
	return false;
}

bool HeardlessPotion::openDoor(Key & obj)
{
	return false;
}

bool HeardlessPotion::openDoor(std::shared_ptr<Items>& obj)
{
	return false;
}

bool HeardlessPotion::usedItem(Thief & obj, mapViewPass& mapObj)
{
	return obj.usedItem(*this, mapObj);
}




void HeardlessPotion::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

sf::FloatRect HeardlessPotion::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f HeardlessPotion::getPosition() const
{
	return m_sprite.getPosition();
}

void HeardlessPotion::loadTexture(const std::string & name)
{
	// get the texture
	m_sprite.setTexture(ResourceManeger::getInstance().getTexture(name));

	// get the texture pos on the texture
	m_sprite.setTextureRect(ResourceManeger::getInstance().getTexturePos(name));

}


void HeardlessPotion::setPosition(float x, float y)
{
	m_sprite.setPosition(x, y);
}