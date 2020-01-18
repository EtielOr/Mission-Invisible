#include "LevelMap.h"

#include "ObjectFactory.h"

bool LevelMap::loadLevel(const int & num)
{
	std::ifstream levelFile; // the reading file

	openLevelFile(levelFile, num); // open the file

	if (!levelFile.is_open()) // case is'nt next level;
		return false;

	levelFile.exceptions(std::ios_base::failbit); // make the file to throw exveptions


	loadMapObject(levelFile); // load the map objects
	loadPlayer(levelFile); // load the player
	loadGuards(levelFile); // load the guards
	loadItems(levelFile); // load the items



	return true;
}

void LevelMap::openLevelFile(std::ifstream &inputFile, int level)
{
	std::string name = "level_" + std::to_string(level) + ".txt"; // name of file 

	inputFile.open(name); // open level file
}

void LevelMap::loadMapObject(std::ifstream &levelFile)
{

	int dimX, dimY; // the map dim

	std::string currObj; // to get the current Obj type

	levelFile >> dimX >> dimY; // get board dim;

	if (dimX <= 0 || dimY <= 0)
		throw(std::logic_error("level size is zero or negative"));

	m_level.resize(dimY); // make dimY rows

	for (int i = 0; i < dimY; i++)
	{
		for (int j = 0; j < dimX; j++)
		{

			levelFile >> currObj; // get current object type
			m_level[i].emplace_back(MapObjectFactory::getInstace().makeObj(currObj, int(j), int(i))); // make object

			if (m_level[i][j] == nullptr) // if the enter item got null
			{
				std::string temp = "there problem in the level file in row: " + std::to_string(i) +
					" col: " + std::to_string(j) + " \"" + currObj + "\" isn't mapobject";
					throw(std::logic_error(temp));
			}

			try
			{
				m_level[i][j]->loadTexture(currObj); // load the texture
			}
			catch (std::exception&e)
			{
				std::string error = e.what();
				error += " in row: " + std::to_string(i) + " in col: " + std::to_string(j);
				throw(std::runtime_error(error));
			}

		}
	}
}



void LevelMap::loadPlayer(std::ifstream &levelFile)
{

	int x, y; // the player start pos
	std::string  currObj, currTexture; // type of object
	levelFile >> currObj; // get player type
	levelFile >> currTexture;

	levelFile >> x >> y; // load player
	m_player = std::make_shared<Thief>(x, y); // make player
	m_player->loadTexture(currTexture);
}

void LevelMap::loadGuards(std::ifstream &levelFile)
{
	int numOfGuard; // how many  guard in the current level
	int x, y; // the guard start pos
	std::string  currObj, currTexture;  // type of object

	levelFile >> numOfGuard; // get how many guards

	for (int i = 0; i < numOfGuard; i++)
	{
		levelFile >> currObj; // get guard type
		levelFile >> currTexture;

		levelFile >> x >> y; // get guard place in the  map
		m_guards.emplace_back(GuardFactory::getInstace().makeObj(currObj, int(x), int(y))); // make new guard


		if (m_guards.back() == nullptr) // if the enter item got null
		{
			std::string temp = "there problem in the level file with guard: " + std::to_string(i) +
				" \"" + currObj + "\" isn't legal guard";
			throw(std::logic_error(temp));
		}

		m_guards.back()->loadTexture(currTexture);

		std::string moves; // to get how the guard will move
		getline(levelFile, moves);

		m_guards[i]->setMove(std::move(moves)); // pass the guard how to move
	}

}

void LevelMap::loadItems(std::ifstream &levelFile)
{

	int numOfItems; // how many  items in the current level
	int x, y; // the item place
	std::string  currObj, currTexture;; // type of object

	levelFile >> numOfItems;

	for (int i = 0; i < numOfItems; i++)
	{
		levelFile >> currObj;
		levelFile >> currTexture;
		levelFile >> x >> y;
		m_items.emplace_back(ItemFactory::getInstace().makeObj(currObj, int(x), int(y)));

		if (m_items.back() == nullptr) // if the enter item got null
		{
			std::string temp = "there problem in the level file with items: " + std::to_string(i) +
				" \"" + currObj + "\" isn't legal item";
			throw(std::logic_error(temp));
		}

		m_items.back()->loadTexture(currTexture);

	}

}

void LevelMap::draw(sf::RenderTarget & target, sf::RenderStates states) const
{


	auto currCenter = target.getView().getCenter();
	auto cuurSize = target.getSize();
	currCenter /= static_cast<float>(TILESIZE);

	int top = std::max(static_cast<int>(currCenter.y- (cuurSize.y / 2)),0); // calc the map top 0 case to is negative

	int bottom = std::min(static_cast<int>((currCenter.y + (cuurSize.y / 2))+ 1),  // calc the map bottom
		static_cast<int>(m_level.size())); // case bottom out side the map

	int left = std::max(static_cast<int>((currCenter.x - (cuurSize.x/2) )),0);


	int right =  std::min(static_cast<int>((currCenter.x+ (cuurSize.x/ 2)) )+1,
		static_cast<int>(m_level[0].size()));         // case bottom out side the map


	for (int i = top; i < bottom; i++) // draw the current view map
		for (int j = left; j < right; j++)
		{
			if (m_level[i][j] != nullptr)
				target.draw(*m_level[i][j]);
		}




	for (auto &guard : m_guards) // draw the guards
		target.draw(*guard);

	for (auto &item : m_items) // draw the items
		target.draw(*item);

	target.draw(*m_player); // draw the player



}

