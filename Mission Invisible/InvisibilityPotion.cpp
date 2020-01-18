#include "InvisibilityPotion.h"
#include "Key.h"
#include "ObjectFactory.h"
#include "Door.h"
#include "Thief.h"
#include "LevelMap.h"

bool InvisibilityPotion::isRegisterFactory = registerInItemsFactory<InvisibilityPotion>("InvisibilityPotion"); // register on the factory


InvisibilityPotion::InvisibilityPotion(const int & x, const int & y)
{
	m_sprite.setPosition(float(x)*TILESIZE, float(y)*TILESIZE);
}

bool InvisibilityPotion::collideItem(const Thief& obj)
{
	return Collision::ThifeAndItems(obj, *this);
}


bool InvisibilityPotion::openDoor(Door & obj)
{
	return false;
}

bool InvisibilityPotion::openDoor(Key & obj)
{
	return false;
}

bool InvisibilityPotion::openDoor(std::shared_ptr<Items>& obj)
{
	return false;
}

bool InvisibilityPotion::usedItem(Thief & obj, mapViewPass& mapObj)
{
	return obj.usedItem(*this, mapObj);
}




void InvisibilityPotion::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

sf::FloatRect InvisibilityPotion::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f InvisibilityPotion::getPosition() const
{
	return m_sprite.getPosition();
}

void InvisibilityPotion::loadTexture(const std::string & name)
{
	// get the texture
	m_sprite.setTexture(ResourceManeger::getInstance().getTexture(name));

	// get the texture pos on the texture
	m_sprite.setTextureRect(ResourceManeger::getInstance().getTexturePos(name));

}


void InvisibilityPotion::setPosition(float x, float y)
{
	m_sprite.setPosition(x, y);
}