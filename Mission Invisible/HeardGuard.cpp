#include "HeardGuard.h"

#include "Thief.h"
#include "ObjectFactory.h"


bool HeardGuard::isRegisterFactory = registerInGuardFactory<HeardGuard>("HeardGuard"); // register on the factory

HeardGuard::HeardGuard(const int & x, const int & y) :
	m_circle(HEARD_RADIUS) , stats(MOVEING_ST),
	moveColiison(std::make_unique<MoveAndColiisionWithMap>(m_sprite,*this))
{
	m_sprite.setPosition(float(x)*TILESIZE, float(y)*TILESIZE);

	m_circle.setFillColor(GUARD_TIHIEF_OUTSIDE); // color of circle
	m_circle.setPosition(m_sprite.getPosition().x + TILESIZE / 2 - m_circle.getRadius()
		, m_sprite.getPosition().y + TILESIZE / 2 - m_circle.getRadius()); // the circle pos

}

void HeardGuard::setMove(std::string &&moves)
{
	static std::map<const std::string, const MOVE_POS> cmdMap
		= { { "UP",UP_CM },{ "DOWN",DOWN_CM },{ "LEFT",LEFT_CM },{ "RIGHT",RIGHT_CM }
	,{ "LOOK_UP", LOOK_UP_CM },{ "LOOK_DOWN",LOOK_DOWN_CM },{ "LOOK_LEFT",LOOK_LEFT_CM },{ "LOOK_RIGHT",LOOK_RIGHT_CM } }; // make map for string to enum

	std::stringstream ss(moves); // to read from string
	std::string currData; // the curr data that get
	std::string moveType; // the move Type

	float heardRadiusFactor;

	ss >> speed; // get speed
	ss >> heardRadiusFactor; // get see Radius

	m_circle.setRadius(HEARD_RADIUS*heardRadiusFactor); // set the seeRadius

	ss >> moveType; // read what type of move to do
	std::vector<MOVE_POS> temp; // how to move




	while (!ss.eof()) // read until end of line
	{
		ss >> currData; // get current data
		auto currCmd = cmdMap.find(currData);


		if (currCmd == cmdMap.end()) // case enter not legal move
			throw(std::logic_error(currData + " is not legal guard move"));

		temp.push_back(currCmd->second); // make new curr cmd;


	}
	if (temp.size() == 0)
		throw(std::logic_error("guard move is empty"));

	if(moveType == "CL")
		m_moveTo = std::make_unique<CircularMove>(std::move(temp));

	else if (moveType == "BF")
		m_moveTo = std::make_unique<GoAndReverseMove>(std::move(temp));

	else 
		throw(std::logic_error(moveType + " is not legal guard move logic"));
}

void HeardGuard::collideWith(const Wall & obj)
{
	moveColiison->collideWith(obj);
}

void HeardGuard::collideWith(Door & obj)
{
	moveColiison->collideWith(obj);
}

void HeardGuard::collideWith(Thief& obj)
{
	if (obj.getState() != HERADLESS && Collision::ThiefAndHeradCircle(obj, m_circle))
	{
		stats = STANDING_ST;
		m_circle.setFillColor(GUARD_TIHIEF_INSIDE);
		obj.lostLife();
		if (ResourceManeger::getInstance().getSound(LOST_LIFE_SD).getStatus() != sf::SoundSource::Status::Playing)
		{
			ResourceManeger::getInstance().getSound(LOST_LIFE_SD).play();
			ResourceManeger::getInstance().getSound(LOST_LIFE_SD).setLoop(false);
			ResourceManeger::getInstance().getSound(LOST_LIFE_SD).setVolume(100.f);
		}

	}

	else
	{
		stats = MOVEING_ST;
		m_circle.setFillColor(GUARD_TIHIEF_OUTSIDE);
	}

	obj.collideWith(*this);

}

bool HeardGuard::isShootArrow()
{
	return false; // heard guard can't shoot arrow
}




std::pair<sf::Vector2f, sf::Vector2f> HeardGuard::getArrowData()
{
	throw(std::logic_error("HeardGuard cann't shoot arrow"));
	return std::make_pair(sf::Vector2f(0, 0), sf::Vector2f(0, 0));

}

void HeardGuard::collideWith(DynamicObject&obj)
{
	obj.collideWith(*this);
}

void HeardGuard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_circle);
	target.draw(m_sprite);

}


void HeardGuard::update(mapViewPass& mapObj)
{

	if (stats == MOVEING_ST)
	{
		moveColiison->move(m_moveTo->getMove(speed), mapObj);


		m_circle.setPosition(m_sprite.getPosition().x + TILESIZE / 2 - m_circle.getRadius() // move the circle
			, m_sprite.getPosition().y + TILESIZE / 2 - m_circle.getRadius());
	}


}

sf::FloatRect HeardGuard::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f HeardGuard::getPosition() const
{
	return m_sprite.getPosition();
}

void HeardGuard::loadTexture(const std::string & name)
{
	// get the texture
	m_sprite.setTexture(ResourceManeger::getInstance().getTexture(name));

	// get the texture pos on the texture
	m_sprite.setTextureRect(ResourceManeger::getInstance().getTexturePos(name));

}