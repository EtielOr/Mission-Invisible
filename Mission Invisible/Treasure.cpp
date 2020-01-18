#include "Treasure.h"
#include "ObjectFactory.h"
#include "MoveAndColiisionWithMap.h"

bool Treasure::isRegisterFactory = registerInMapFactory<Treasure>(53,58); // register on the factory




Treasure::Treasure(const int & x, const int & y)
{
	m_sprite.setPosition(float(x)*TILESIZE, float(y)*TILESIZE);
}

void Treasure::collideWith(DynamicObject & obj)
{
	obj.collideWith(*this);
}


bool Treasure::openDoor(Door & obj)
{
	return false;
}

bool Treasure::openDoor(Key & obj)
{
	return false;
}

bool Treasure::openDoor(std::shared_ptr<Items> &)
{
	return false;
}

bool Treasure::isPassAble()
{
	return true;
}

void Treasure::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

sf::FloatRect Treasure::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f Treasure::getPosition() const
{
	return m_sprite.getPosition();
}

void Treasure::loadTexture(const std::string & name)
{
	// get the texture
	m_sprite.setTexture(ResourceManeger::getInstance().getTexture(name));

	// get the texture pos on the texture
	m_sprite.setTextureRect(ResourceManeger::getInstance().getTexturePos(name));

}