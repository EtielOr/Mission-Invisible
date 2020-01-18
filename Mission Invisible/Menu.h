#pragma once

#include "ResourceManeger.h"
#include "Const.h"
#include "CommandMap.h"
#include <SFML\Graphics.hpp>
#include <string>

/* used to make game menu */


const int FONTSIZE = 30;
const int SPACE = FONTSIZE + FONTSIZE / 2;
const float  MAIN_SCREEN_SIZE = 720.f;
const sf::Color BUTTON_DEFAULT_COLOR = sf::Color(102, 102, 0); // draw yellow color
const sf::Color BUTTON_SELECT_COLOR = sf::Color::Yellow;
const sf::Color QUESTION_TEXT_COLOR = sf::Color::Red;
const sf::Color TRANSPARENT_BLACK_COLOR = sf::Color(25, 25, 25, 5);	// ttansparent black color
const sf::Color YELLOW_COLOR = sf::Color::Yellow; // green color for the game

struct MenuItem
{
	sf::Text _text;
	std::string  _cmd;
	// to make new MenuItem
	MenuItem(const std::string &cmd, const std::string &text);
};

class Menu
{
public:
	// constactor make new Meun
	Menu();

	// ask the user if he sure to do someing return user answer
	bool askSure(std::string question);
	// open the mainMenu
	void openMainMenu(sf::RenderWindow &window);

	void openPauseMenu(sf::RenderWindow &window);


private:
	// to hold game Main Menu
	std::vector<MenuItem> mainMenu;
	// the game  Pause Meun
	std::vector<MenuItem>  pauseMenu;

	// to ask if the user if he Sure the opsition he chose
	std::vector<MenuItem>  sureMenu;


	// make the Main Menu to the Game
	void makeMainMenu();
	// make the Pause Menu to the Game
	void makePauseMenu();
	// make the SureMenu
	void makeSureMenu();

	// draw menu to the screen
	void drawMenu(sf::RenderWindow &window, std::vector<MenuItem> menu);

	// move the Menu left
	void moveLeft(int &selectBotton, std::vector<MenuItem> &currMenu);
	// move the Menu Right
	void moveRight(int &selectBotton, std::vector<MenuItem> &currMenu);
	// move the Menu Up
	void moveUp(int &selectBotton, std::vector<MenuItem> &currMenu);
	// move the Menu Down
	void moveDown(int &selectBotton, std::vector<MenuItem> &currMenu);

	// to hold the game title
	sf::Text gameTitle;

};