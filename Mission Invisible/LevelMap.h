#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include <list>

#include "Const.h"
#include "ObjectFactory.h"
#include "Thief.h"


// class to hold the current level map

// class to hold the curr level map

class LevelMap : public sf::Drawable
{
public:

	bool loadLevel(const int &num); // get level number and load it return false if isn't level file by the number



	class mapView;  //use to view the map
	class levelView; // use to view the whole level

	inline mapView make_mapView(); // make makeView
	inline levelView make_levelView(); // make levelView


private:
	std::vector<std::vector<std::shared_ptr<MapObject>>> m_level; // the currnet maps object
	std::vector<std::vector<bool>> m_grpah; // graph of the map
	std::vector<std::shared_ptr<Guard>> m_guards; // the guards in hte map
	std::list<std::shared_ptr<Items>>  m_items; // the items in the map
	std::shared_ptr<Thief> m_player; // the playet


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // to draw the map

	void openLevelFile(std::ifstream &inputFile, int level); // to open the current file to the level
	void loadMapObject(std::ifstream &levelFile); // to load the current map objects
	void loadPlayer(std::ifstream &levelFile); // to load the player
	void loadGuards(std::ifstream &levelFile); // to load the gaurd
	void loadItems(std::ifstream &levelFile); // to load the items
};

class LevelMap::mapView // used to view the map
{
public:
	mapView(LevelMap& currMap) : m_currMap(&currMap) {};
	size_t size() const; // return map number of rows

	~mapView() {};
	inline const std::vector<std::shared_ptr<MapObject>>&operator[](int y) const; // to view objects on the map
	inline const sf::FloatRect getThiefBounds();


protected:
	LevelMap *m_currMap; // the call map

};

class LevelMap::levelView : public LevelMap::mapView
{
public:
	levelView(LevelMap& currMap) : mapView(currMap) {};


	inline std::shared_ptr<Thief> getPlayer(); // to view the player
	inline std::list < std::shared_ptr<Items>> & getItems();
	inline std::vector<std::shared_ptr<Guard>> & getGuards();

private:
};


class mapViewPass // used to bayypass compiler problem
{
public:
	mapViewPass(LevelMap::mapView &a) : mapV(a) {};
	~mapViewPass() {};
	inline LevelMap::mapView&  pass() const { return mapV; }

protected:
	LevelMap::mapView& mapV;
};





inline LevelMap::mapView LevelMap::make_mapView()
{
	return mapView(*this);
}

inline LevelMap::levelView LevelMap::make_levelView()
{
	return levelView(*this);
}

inline size_t LevelMap::mapView::size() const
{
	return m_currMap->m_level.size();
}



inline const std::vector<std::shared_ptr<MapObject>>& LevelMap::mapView::operator[](int y) const
{
	return m_currMap->m_level[y];
}

inline const sf::FloatRect LevelMap::mapView::getThiefBounds()
{
	return m_currMap->m_player->getGlobalBounds();
}

inline std::list<std::shared_ptr<Items>>& LevelMap::levelView::getItems()
{
	return  m_currMap->m_items;
}

inline std::vector<std::shared_ptr<Guard>>& LevelMap::levelView::getGuards()
{
	return m_currMap->m_guards;
}

inline std::shared_ptr<Thief> LevelMap::levelView::getPlayer()
{
	return m_currMap->m_player;
}