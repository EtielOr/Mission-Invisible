#pragma once

#include <SFML/Graphics.hpp>
#include <string>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;



const int TILESIZE = 24; // the tile size of the game


#define TEXTURE_FILE std::string("texture.png")
#define FONT_FILE std::string("font.ttf")

#define TEXTURE_DATA_FILE std::string("tilepos.txt")

const std::string RESTART_LEVEL_CMD = "restart level";
const std::string NEXT_LEVEL_CMD = "next level";
const std::string SHOOT_ARROW = "shoot arrow";

const std::string NEW_GAME_CMD = "new game";
const std::string EXIT_GAME_CMD = "exit game";
const std::string CONTINUE_CMD = "contine game";
const std::string START_MENU_CMD = "nmeun";

const float BASE_SPEED = 1.f; // base speed
const float HEARD_RADIUS = TILESIZE * 2; // head guard base Radius


const sf::Color GUARD_TIHIEF_OUTSIDE_START = sf::Color(128, 128, 0, 128); // color when  outdie guard
const sf::Color GUARD_TIHIEF_OUTSIDE = sf::Color(255, 255, 153, 130); // color when  outdie guard see end

const sf::Color GUARD_TIHIEF_INSIDE_START = sf::Color(128, 0, 0, 128);
const sf::Color GUARD_TIHIEF_INSIDE = sf::Color(255, 0, 0, 130);

const float POTION_TIME = 7.f; // how many sec potion are

enum MOVE_POS {
	UP_CM, DOWN_CM, LEFT_CM, RIGHT_CM, LOOK_UP_CM, LOOK_DOWN_CM, LOOK_LEFT_CM, LOOK_RIGHT_CM
};

enum GUARD_STATS { MOVEING_ST, STANDING_ST};

enum SOUNDS {ARROW_SD,LOST_LIFE_SD,END_LEVEL_SD,PICK_ITEM_SD,DEAD_SD };

