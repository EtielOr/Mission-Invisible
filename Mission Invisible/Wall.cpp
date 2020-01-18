#include "Wall.h"

#include "ObjectFactory.h"
#include "MoveAndColiisionWithMap.h"

bool Wall::isRegisterFactory = registerInMapFactory<Wall>(11,51) && registerInMapFactory<Wall>(59,60); // register on the factory

Wall::Wall(const int & x, const int & y)
{
	m_sprite.setPosition(float(x)*TILESIZE, float(y)*TILESIZE);
}

void Wall::collideWith(DynamicObject & obj)
{
	obj.collideWith(*this);
}

bool Wall::openDoor(Door & obj)
{
	return false;
}

bool Wall::openDoor(Key & obj)
{
	return false;
}

bool Wall::openDoor(std::shared_ptr<Items>& obj)
{
	return false;
}


bool Wall::isPassAble()
{
	return false;
}

void Wall::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

sf::FloatRect Wall::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f Wall::getPosition() const
{
	return m_sprite.getPosition();
}

void Wall::loadTexture(const std::string & name)
{
	// get the texture
	m_sprite.setTexture(ResourceManeger::getInstance().getTexture(name));

	// get the texture pos on the texture
	m_sprite.setTextureRect(ResourceManeger::getInstance().getTexturePos(name));

}