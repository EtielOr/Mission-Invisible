#pragma once
#include <memory>
#include"InvisibilityPotion.h"
#include <vector>
#include "DynamicObject.h"
#include "MoveAndColiisionWithMap.h"
#include "MoveLogicKeyboard.h"
#include "ItemBag.h"

class Items;
class HeardlessPotion;
class Key;
class mapViewPass;
class SpeedPotion;

const int MAX_ITEMS = 10; // how many items thief can hold
enum THIEF_STATE { NORMAL, HERADLESS, INVISIBIlITY,SPEED};

class Thief : public DynamicObject
{
public:
	Thief(const int &x, const int &y);


	virtual void update(mapViewPass& mapObj); // update the thief

	virtual void collideWith(const Guard &obj);
	virtual void collideWith(DynamicObject&);
	virtual void collideWith(const Wall&obj);
	virtual void collideWith(Door&obj);
	virtual void collideWith(const Floor&) {};
	virtual void collideWith(const Treasure&);

	bool pickItem(std::shared_ptr<Items> &obj); // when pick item return true is there palce for the item flase whebn not


	virtual bool usedItem(Key& obj, mapViewPass& mapObj);
	virtual bool usedItem(HeardlessPotion& obj, mapViewPass& mapObj);
	virtual bool usedItem(InvisibilityPotion& obj, mapViewPass& mapObj);
	virtual bool usedItem(SpeedPotion& obj, mapViewPass& mapObj);

	void drawData(sf::RenderTarget &target); // draw data to window

	inline void moveItemBagNext(); // move the item bag next
	inline void moveItemBagPrev(); // move the item bag prev
	void usedItem(mapViewPass & mapObj); // the thief will used item

	void lostLife();
	THIEF_STATE getState() const;


	virtual sf::FloatRect getGlobalBounds()  const; // return Sprite bounds
	virtual sf::Vector2f getPosition() const;  // return Sprite pos

	virtual void loadTexture(const std::string &name); // get what texture to load and load it




private:
	sf::Vector2f startPos; // the start postion of the object
	float life; // the curr life
	sf::Clock lifeLostDelay; // the life lost Delay

	THIEF_STATE state; // current stats
	sf::Clock stateTimer; // how many sec in the curr state
	std::unique_ptr<MoveAndColiisionWithMap> moveColiison; // to move and collied
	std::unique_ptr<MoveLogic> m_moveTo; //the move logic of the thief
	ItemBag m_bag; // item bag


	sf::RectangleShape lifeBar; // the thief life
	sf::RectangleShape currlife; // the curr life
	sf::CircleShape poitionTime;
	sf::Color poitionTimeColor;

	bool openDoor(Key& obj, mapViewPass& mapObj); // used to opeon door

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // to draw the map
};

inline void Thief::moveItemBagNext()
{
	m_bag.moveNextItem();
}
inline void Thief::moveItemBagPrev()
{
	m_bag.movPrevItem();
}