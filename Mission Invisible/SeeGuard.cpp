#include "SeeGuard.h"

#include "Thief.h"
#include "ObjectFactory.h"
#include "LevelMap.h"
#include "CommandMap.h"

const size_t SEE_LINES = 30; // form how many line the guard made of 
const size_t SEE_RANGE = TILESIZE * 6; // the see  range
const int LINE_JUMP = 3; // how many point to move every line
const int DEG_JUMP = 3; // deg jump form line to next line
const float ARROW_SHOOT_TIME = 700.f; // in mile sec

bool SeeGuard::isRegisterFactory = registerInGuardFactory<SeeGuard>("SeeGuard"); // register on the factory

SeeGuard::SeeGuard(const int & x, const int & y) :
	moveColiison(std::make_unique<MoveAndColiisionWithMap>(m_sprite, *this))
	, stauts(MOVEING_ST), shootArrow(false)
{
	m_sprite.setPosition(float(x)*TILESIZE, float(y)*TILESIZE);
	m_see.resize(SEE_LINES +1); // 40 lines + 1 sourcres point
	m_see.setPrimitiveType(sf::PrimitiveType::TriangleFan);
	updateTime.restart(); // restart update time
}

void SeeGuard::setMove(std::string &&moves)
{
	static std::map<const std::string, const MOVE_POS> cmdMap
		= { { "UP",UP_CM },{ "DOWN",DOWN_CM },{ "LEFT",LEFT_CM },{ "RIGHT",RIGHT_CM }
	  ,{ "LOOK_UP", LOOK_UP_CM },{ "LOOK_DOWN",LOOK_DOWN_CM },{ "LOOK_LEFT",LOOK_LEFT_CM },{ "LOOK_RIGHT",LOOK_RIGHT_CM } }; // make map for string to enum
	


	std::stringstream ss(moves); // to read from string
	std::string currData; // the curr data that get
	std::string moveType; // the move Type

	ss >> speed; // get spped
	ss >> seeRangeFactor; // the see range Factor

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

	if(temp.size() == 0)
		throw(std::logic_error("guard move is empty"));

	if (moveType == "CL")
		m_moveTo = std::make_unique<CircularMove>(std::move(temp));

	else if (moveType == "BF")
		m_moveTo = std::make_unique<GoAndReverseMove>(std::move(temp));

	else
		throw(std::logic_error(moveType + " is not legal guard move logic"));
}

void SeeGuard::collideWith(const Wall & obj)
{
	moveColiison->collideWith(obj);
}

void SeeGuard::collideWith(Door & obj)
{
	moveColiison->collideWith(obj);
}

void SeeGuard::collideWith(Thief& obj)
{
	//because this will be slow we text it in the update
	// to not 2 time make See viutalr

	if (thiefIsIn && obj.getState() != INVISIBIlITY)
	{
		stauts = STANDING_ST;

		if (m_see[0].color != GUARD_TIHIEF_INSIDE_START)
		{
			m_see[0].color = GUARD_TIHIEF_INSIDE_START;
			for (size_t i = 1; i < m_see.getVertexCount(); i++)
				m_see[i].color = GUARD_TIHIEF_INSIDE;
		}

		if (arrowShootTimer.getElapsedTime().asMilliseconds() > ARROW_SHOOT_TIME)
		{
			arrowShootStart = sf::Vector2f(m_sprite.getPosition().x + TILESIZE/2, m_sprite.getPosition().y + TILESIZE / 2);
			arrowShootMove = obj.getPosition() - arrowShootStart;
			arrowShootMove.x += TILESIZE / 2;
			arrowShootMove.y += TILESIZE / 2;
										// to make vector as 1 vector
			float vect = std::sqrt(arrowShootMove.x*arrowShootMove.x + arrowShootMove.y* arrowShootMove.y);
			arrowShootMove /= vect;
			shootArrow = true;
			CommandMap::getInstace().doCommand(SHOOT_ARROW);
			shootArrow = false;
			// shoot arrow
			arrowShootTimer.restart();
		}
	}
	else
	{
		arrowShootTimer.restart();
		stauts = MOVEING_ST;
	}


	obj.collideWith(*this);

}




void SeeGuard::collideWith(DynamicObject&obj)
{
	obj.collideWith(*this);
}

bool SeeGuard::isShootArrow()
{
	return shootArrow;
}

std::pair<sf::Vector2f, sf::Vector2f> SeeGuard::getArrowData()
{
	return std::make_pair(arrowShootStart, arrowShootMove);
}

void SeeGuard::updataSee(mapViewPass & mapObj)
{
				// set orgin point in guard center
	m_see[0].position = sf::Vector2f(m_sprite.getPosition().x + TILESIZE / 2, m_sprite.getPosition().y + TILESIZE / 2);
	m_see[0].color = GUARD_TIHIEF_OUTSIDE_START;


	auto thiefBounds = mapObj.pass().getThiefBounds();
	thiefIsIn = false;



	int startDeg = getStartDeg(); // the start and the end of the look



	for (size_t i = 1; i < m_see.getVertexCount(); i++)
	{
		int currDeg = startDeg + static_cast<int>(i) * DEG_JUMP;

		if (currDeg >= 360)
			currDeg -= 360; // when go full circle (same currDeg = 360 % currDeg) 

		double posX = std::cos(currDeg * M_PI / 180.0); // the currDeg on circle 
		double posY = std::sin(currDeg * M_PI / 180.0);

		sf::Vector2f temp(m_see[0].position); // start on the center

		for (int lineLength = 1; lineLength < static_cast<int>(SEE_RANGE*seeRangeFactor); lineLength += LINE_JUMP)
		{
												// the currplace the line is in
			sf::Vector2i currPlace(static_cast<int> (temp.x) / TILESIZE, static_cast<int> (temp.y) / TILESIZE);

			if (mapObj.pass().size() <= static_cast<size_t>(currPlace.y) 
				|| 0 > static_cast<size_t>(currPlace.y) || 0 > static_cast<size_t>(currPlace.x)
				|| mapObj.pass()[0].size() <= static_cast<size_t>(currPlace.x)) // to stop lock outside the map
				break; 

			if ( !  mapObj.pass()[currPlace.y][currPlace.x]->isPassAble()) // when the palce is'nt pass able
				break;

			if (thiefBounds.contains(temp))
				thiefIsIn = true;


			temp.x += static_cast<float>(posX*LINE_JUMP); // move the line for the next pos
			temp.y += static_cast<float>(posY*LINE_JUMP);

		}

		m_see[i].position = temp; // the point last palce
		m_see[i].color = GUARD_TIHIEF_OUTSIDE;
	}

}

int SeeGuard::getStartDeg()
{

	switch (m_moveTo->getLastPos())  // where the guard look now
	{
	case UP_CM:
	case LOOK_UP_CM:
		return 270 - (SEE_LINES* DEG_JUMP) / 2;
		break;
	case DOWN_CM:
	case LOOK_DOWN_CM :
		return 90 - (SEE_LINES* DEG_JUMP) / 2;
		break;
	case LEFT_CM:
	case LOOK_LEFT_CM :
		return 180 - (SEE_LINES* DEG_JUMP) / 2;
		break;
	case RIGHT_CM:
	case LOOK_RIGHT_CM:
		return 360 - (SEE_LINES* DEG_JUMP) / 2; // 360 == 0
		break;
	default:
		return 0;
		break;
	}
}

void SeeGuard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_see);
	target.draw(m_sprite);

}

void SeeGuard::update(mapViewPass& mapObj)
{
	
	if(stauts == MOVEING_ST)
		moveColiison->move(m_moveTo->getMove(speed), mapObj);


	if (updateTime.getElapsedTime().asMilliseconds() >= 30.f)
	{
		updataSee(mapObj);
		updateTime.restart();
	}


}


sf::FloatRect SeeGuard::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f SeeGuard::getPosition() const
{
	return m_sprite.getPosition();
}

void SeeGuard::loadTexture(const std::string & name)
{
	// get the texture
	m_sprite.setTexture(ResourceManeger::getInstance().getTexture(name));

	// get the texture pos on the texture
	m_sprite.setTextureRect(ResourceManeger::getInstance().getTexturePos(name));

}