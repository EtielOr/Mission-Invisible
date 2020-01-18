#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Menu.h"
#include"LevelMap.h"
#include "Arrow.h"

// this class used as controler for levels

class LevelController
{
public:

	void run(); // run the levels


	void restart(); // to restart the level
	void nextLevel(); // to go to the next level
	void addArrow(); // add new arrow to the game
	void newGame();
	void openStartMenu();

	void exit(); // to exit game

	static	LevelController& getInstace();

	LevelController(const LevelController &) = delete;
	auto operator=(const LevelController &) = delete;



private:
	LevelController(); // make new level controller

	Menu m_Meun;

	sf::View gameView; // to handle the view
	sf::View dataView; // the data like item view


	int levelNum; // the curruet level number
	std::unique_ptr<LevelMap> currLevel; // the current map
	std::shared_ptr<LevelMap::mapView> mapObj; // to view the map
	std::shared_ptr<LevelMap::levelView> levelObj; // to view the level
	sf::RenderWindow window; // the game window

	std::list < std::unique_ptr<Arrow>> m_arrow; // to hold shot arrows


	bool levelRestart; // to stop loop in middle if the level restart or move to new level

	bool loadLevel(const int& levelNum); // get level and load the level and return if the level exsit
	void updateLevel(); // to update the level

	void eventHandler(sf::RenderWindow& window); // handler event in the window

};

