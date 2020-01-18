#include "LevelController.h"

#include "CommandMap.h"
#include "CommandReStartLevel.h"
#include "CommandNextLevel.h"
#include "CommandAddArrow.h"
#include "CommandExitGame.h"
#include "CommandNewGame.h"
#include "CommandOpenStartMenu.h"
#include <SFML/Graphics.hpp>

enum MENU{ START_MENU,PASUE_NENU,EXIT_MENU};

LevelController::LevelController() :
	levelNum(1), // start on first level
	window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Mission Invisible", sf::Style::Close)
{	
															// register restart level cmd
	CommandMap::getInstace().registerCommand(RESTART_LEVEL_CMD, std::make_unique<CommandRestartLevel>(*this));
												// register next level cmd
	CommandMap::getInstace().registerCommand(NEXT_LEVEL_CMD, std::make_unique<CommandNextLevel>(*this));


	CommandMap::getInstace().registerCommand(SHOOT_ARROW, std::make_unique<CommandAddArrow>(*this));


	CommandMap::getInstace().registerCommand(NEW_GAME_CMD, std::make_unique<CommandNewGame>(*this));
	CommandMap::getInstace().registerCommand(EXIT_GAME_CMD, std::make_unique<CommandExitGame>(*this));

	CommandMap::getInstace().registerCommand(START_MENU_CMD, std::make_unique<CommandOpenStartMenu>(*this));

	gameView = window.getView();


	float xSize = static_cast<float>(window.getSize().x) * 1.f;
	float ySize = static_cast<float>(TILESIZE);

	float xFloat = (float)xSize / window.getSize().x;
	float yFloat = (float)ySize / window.getSize().y;

	dataView.reset(sf::FloatRect(0.f, 0.f, xSize, ySize));
	dataView.setViewport(sf::FloatRect(0.f,0.f, xFloat, yFloat));


	loadLevel(1);
}



bool LevelController::loadLevel(const int & levelNum)
{
	currLevel = std::make_unique<LevelMap>(); // make level
	m_arrow.clear(); // cleat the arrows in the game
	if (currLevel->loadLevel(levelNum)) // load the level and return if the level exist
	{
		mapObj = std::make_shared<LevelMap::mapView>(currLevel->make_mapView());
		levelObj = std::make_shared<LevelMap::levelView>(currLevel->make_levelView());
		return true;
	}
	return false;
}

void LevelController::updateLevel()
{
	mapViewPass mapPass(*mapObj); // to pass the map

	levelObj->getPlayer()->update(mapPass); // update the player

	for (auto &x : levelObj->getGuards())
	{
		x->update(mapPass);  // update the Guards
		x->collideWith(*levelObj->getPlayer());  // check collides with guard and player
	}

	for (auto x = levelObj->getItems().begin(); x != levelObj->getItems().end(); x++) // check collide with player and items
	{
		if ((*x)->collideItem(*levelObj->getPlayer()))
		{
			if ((levelObj->getPlayer())->pickItem(*x)) // if able to pick item pick it up
				levelObj->getItems().erase(x);
			break; // break because you can't collied with 2 item in the same time
		}

	}

	for (auto x = m_arrow.begin(); x != m_arrow.end(); ++x)
	{
		(*x)->update(mapPass);
		if ((*x)->isEnded())
		{
			x = m_arrow.erase(x); 
				break;				// to fix error
		}
		else
			(*x)->collideWith(*levelObj->getPlayer());
	}



}

void LevelController::eventHandler(sf::RenderWindow& window)
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			if (m_Meun.askSure("Are you suer you want to quit?"))
				window.close();
			break;
		case sf::Event::Resized:
			gameView.setSize((float)event.size.width, (float)event.size.height);
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::C)
				levelObj->getPlayer()->moveItemBagPrev();
			else if (event.key.code == sf::Keyboard::V)
				levelObj->getPlayer()->moveItemBagNext();
			else if (event.key.code == sf::Keyboard::Space)
			{
				mapViewPass mapPass(*mapObj); // to pass the map
				levelObj->getPlayer()->usedItem(mapPass);
			}
			else if (event.key.code == sf::Keyboard::Escape)
				m_Meun.openPauseMenu(window);

			break;
		default:
			break;
		}
	}
}


void LevelController::run()
{


	m_Meun.openMainMenu(window);

	sf::Clock updateClock; // the game update clock
	updateClock.restart(); // restart the clock

	 if(!loadLevel(levelNum))// load the first level
		throw(std::runtime_error("Error level_1.txt is missing")); // case fail to load first level

	while (window.isOpen())
	{

		eventHandler(window); //

		if (updateClock.getElapsedTime().asMilliseconds() > 8.0f) // if need to update
		{
			updateLevel(); // update the level

			updateClock.restart(); // restart the clock

			gameView.setCenter(levelObj->getPlayer()->getPosition());

		}

		if (levelRestart)
		{
			if (!loadLevel(levelNum)) // if didn't able to load next level the player win
			{
				levelNum = 1;
				loadLevel(levelNum);
			}
			levelRestart = false;
		}


		window.clear(); // draw the level

		window.setView(gameView);
		window.draw(*currLevel);

		for (auto &x : m_arrow)
			window.draw(*x);


		window.setView(dataView);
		levelObj->getPlayer()->drawData(window);


		window.display();
	}
}

void LevelController::restart()
{
	levelRestart = true;
}

void LevelController::nextLevel()
{
	++levelNum; // add to the next level

	levelRestart = true;

}

void LevelController::addArrow()
{
	for (auto &x : levelObj->getGuards())
	{
		if (x->isShootArrow()) // if the the guard that shoot arrow
		{
			auto arrowData = x->getArrowData();
			m_arrow.emplace_back(std::make_unique<Arrow>(arrowData.first, arrowData.second));
			(m_arrow.back())->loadTexture("AR");

			ResourceManeger::getInstance().getSound(ARROW_SD).play();
			ResourceManeger::getInstance().getSound(ARROW_SD).setLoop(false);
			ResourceManeger::getInstance().getSound(ARROW_SD).setVolume(100.f);
		}

	}
}

void LevelController::newGame()
{
	levelNum = 1; // to restart from level 1

	levelRestart = true;

}

void LevelController::openStartMenu()
{
	m_Meun.openMainMenu(window);
}

void LevelController::exit()
{
	window.close();
}

LevelController& LevelController::getInstace()
{
	static LevelController  conlevel;

	return conlevel;
}
