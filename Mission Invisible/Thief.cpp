#include "Thief.h"
#include "MoveAndColiisionWithMap.h"
#include "Door.h"
#include "MapObject.h"
#include "LevelMap.h"
#include "Key.h"
#include "HeardlessPotion.h"
#include "Treasure.h"
#include "Collision.h"
#include "CommandMap.h"



Thief::Thief(const int & x, const int & y) :
	startPos(float(x), float(y)), state(NORMAL),
	moveColiison(std::make_unique<MoveAndColiisionWithMap>(m_sprite, *this)),
	life(100.f),
	lifeBar(sf::Vector2f(100.f * 2, static_cast<float>(TILESIZE))),
	currlife(sf::Vector2f(0, static_cast<float>(TILESIZE))),
	poitionTime((static_cast<float>(TILESIZE / 2))),
	poitionTimeColor(255, 215, 0, 0), m_moveTo(std::make_unique<MoveLogicKeyboard>())
{
	m_sprite.setPosition(float(x)*TILESIZE, float(y)*TILESIZE);

	lifeBar.setPosition(TILESIZE * 13, 0);
	currlife.setPosition(TILESIZE * 13, 0);
	lifeBar.setFillColor(sf::Color(229, 232, 232,128));
	currlife.setFillColor(sf::Color(255,57,43,128));
	poitionTime.setPosition(static_cast<float>(TILESIZE) * 25, 0);
	poitionTime.setFillColor(poitionTimeColor);

}


void Thief::update(mapViewPass & mapObj)
{
	if (state != NORMAL && stateTimer.getElapsedTime().asSeconds() > POTION_TIME)
	{
		if (state == SPEED)
			speed /= 2;

		state = NORMAL;
		m_sprite.setColor(sf::Color::White);
		poitionTimeColor.a = 0;
		poitionTime.setFillColor(poitionTimeColor);

	}
	else if (state != NORMAL)
	{

		poitionTimeColor.a = 255 - static_cast<sf::Uint8>( (stateTimer.getElapsedTime().asMilliseconds() / (POTION_TIME * 1000.f) *220)) ;
		poitionTime.setFillColor(poitionTimeColor);
	}

	moveColiison->move(m_moveTo->getMove(speed), mapObj);


	if (life < 100.f)// if life isn't full add life
	{
		life += 0.03f;
		currlife.setSize(sf::Vector2f((100.f - life) * 2, static_cast<float>(TILESIZE)));
	}

}

void Thief::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}


void Thief::collideWith(const Guard & obj)
{
	if (Collision::ThiefAndGuard(*this, obj)) // case the thief die
		CommandMap::getInstace().doCommand(RESTART_LEVEL_CMD);
}

void Thief::collideWith(const Wall & obj)
{
	moveColiison->collideWith(obj);
}

void Thief::collideWith(Door & obj)
{
	moveColiison->collideWith(obj);
}

void Thief::collideWith(const Treasure &obj)
{
	if (Collision::MapObjectAndDynamicObject(obj, m_sprite))
	{

		ResourceManeger::getInstance().getSound(END_LEVEL_SD).play();
		ResourceManeger::getInstance().getSound(END_LEVEL_SD).setLoop(false);
		ResourceManeger::getInstance().getSound(END_LEVEL_SD).setVolume(100.f);

		CommandMap::getInstace().doCommand(NEXT_LEVEL_CMD); // move to the next level



	}
}

void Thief::collideWith(DynamicObject&obj)
{
	obj.collideWith(*this);
}

bool Thief::pickItem(std::shared_ptr<Items> &obj)
{
	return m_bag.addItem(obj);
}

bool Thief::usedItem(HeardlessPotion& obj, mapViewPass& mapObj)
{
	if (state != NORMAL)
		return false;

	state = HERADLESS;
	stateTimer.restart();
	m_sprite.setColor(sf::Color(76, 76, 76, 255));
	return true;
}

bool Thief::usedItem(InvisibilityPotion & obj, mapViewPass & mapObj)
{
	if (state != NORMAL)
		return false;

		state = INVISIBIlITY;
		stateTimer.restart();
		m_sprite.setColor(sf::Color(128, 128, 128, 128));
		return true;
}

bool Thief::usedItem(SpeedPotion& obj, mapViewPass& mapObj)
{
	if (state != NORMAL)
		return false;

	state = SPEED;
	speed *= 2;
	stateTimer.restart();
	m_sprite.setColor(sf::Color(192,57,43,255));
	return true;
}

void Thief::usedItem(mapViewPass & mapObj)
{
	if (m_bag.getItem() != nullptr) // if there item
	{
		if (m_bag.getItem()->usedItem(*this, mapObj)) // used the item
		{
			m_bag.removeCurrPosItem();
		}
	}
}

void Thief::drawData(sf::RenderTarget & target)
{
	target.draw(lifeBar);
	target.draw(currlife);
	target.draw(m_bag);
	target.draw(poitionTime);
}

bool Thief::usedItem(Key& obj, mapViewPass& mapObj)
{
	return openDoor(obj, mapObj);;
}

void Thief::lostLife()
{
	if (life <= 0)
	{
		ResourceManeger::getInstance().getSound(SOUNDS::DEAD_SD).play();
		ResourceManeger::getInstance().getSound(SOUNDS::DEAD_SD).setLoop(false);
		ResourceManeger::getInstance().getSound(SOUNDS::DEAD_SD).setVolume(100.f);
		CommandMap::getInstace().doCommand(RESTART_LEVEL_CMD);
	}

	if (lifeLostDelay.getElapsedTime().asMilliseconds() > 30)
	{
		life -= 1.8f;
		lifeLostDelay.restart();
	}

}

THIEF_STATE Thief::getState() const
{
	return state;
}

bool Thief::openDoor(Key& obj, mapViewPass& mapObj)
{
	auto map = mapObj.pass();

	sf::Vector2i spritePos = sf::Vector2i(int(m_sprite.getPosition().x / TILESIZE), int(m_sprite.getPosition().y / TILESIZE));
	static const std::array<sf::Vector2i, 6> collisionCheck
		= { sf::Vector2i(0, 0),
		sf::Vector2i(1, 0),
		sf::Vector2i(0, 1),
		sf::Vector2i(1, 1),
		sf::Vector2i(0,-1),
		sf::Vector2i(-1,0)};

	for (size_t i = 0; i < collisionCheck.size(); i++) // look if there door
	{
		sf::Vector2i checkPoint = spritePos + collisionCheck[i];

		if (checkPoint.y < 0 || checkPoint.y >= int(map.size()) ||
			checkPoint.x < 0 || checkPoint.x >= int(map[checkPoint.y].size()))
			continue;

		if (map[checkPoint.y][checkPoint.x]->openDoor(obj)) // if succuse to open door
			return true;
	}

	return false; // case didn't open door
}


sf::FloatRect Thief::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f Thief::getPosition() const
{
	return m_sprite.getPosition();
}

void Thief::loadTexture(const std::string & name)
{
	// get the texture
	m_sprite.setTexture(ResourceManeger::getInstance().getTexture(name));

	// get the texture pos on the texture
	m_sprite.setTextureRect(ResourceManeger::getInstance().getTexturePos(name));

}