#include "Key.h"
#include "ObjectFactory.h"
#include "Door.h"
#include "Thief.h"
#include "LevelMap.h"

bool Key::isRegisterFactory = registerInItemsFactory<Key>("Key"); // register on the factory


Key::Key(const int & x, const int & y)
{
	m_sprite.setPosition(float(x)*TILESIZE, float(y)*TILESIZE);
}

void Key::collideWith(DynamicObject &obj)
{
}

bool Key::collideItem(const Thief& obj)
{
	return Collision::ThifeAndItems(obj, *this);
}

bool Key::usedItem(Thief & obj, mapViewPass& mapObj)
{
	return obj.usedItem(*this, mapObj);
}


bool Key::openDoor(Door & obj)
{
	return obj.openDoor(*this);
}

bool Key::openDoor(Key & obj)
{
	return false;
}

bool Key::openDoor(std::shared_ptr<Items>& obj)
{
	return false;
}

void Key::setPosition(float x, float y)
{
	m_sprite.setPosition(x, y);
}


void Key::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}


sf::FloatRect Key::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f Key::getPosition() const
{
	return m_sprite.getPosition();
}

void Key::loadTexture(const std::string & name)
{
	// get the texture
	m_sprite.setTexture(ResourceManeger::getInstance().getTexture(name));

	// get the texture pos on the texture
	m_sprite.setTextureRect(ResourceManeger::getInstance().getTexturePos(name));

}