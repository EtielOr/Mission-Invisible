#pragma once


#include <vector>
#include <memory>
#include "Const.h"
#include "Items.h"

// used to hold item and used them

const size_t BAG_SIZE = 10;


class ItemBag : public sf::Drawable
{
public:
	ItemBag(); // contractor

	inline bool addItem(std::shared_ptr<Items> &obj); // to pick items
	inline std::shared_ptr<Items> getItem(); // return the currItem



	inline void moveNextItem(); // point on the next item
	inline void movPrevItem();

	inline void removeCurrPosItem(); // remove the item in currPos



private:
	std::vector<std::shared_ptr<Items>> m_bag; // the items in the bag
	size_t currPos; // the currPos in the bag
	sf::RectangleShape itemsRect; // to draw the items
	sf::RectangleShape curPosRect;


	inline void updatecurPosRect(); // update the pos of currPosRect
	inline void updateItemPos(); // update items pos on the screen

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // to draw 
};




inline bool ItemBag::addItem(std::shared_ptr<Items> &obj)
{
	if (m_bag.size() >= BAG_SIZE) // when the item bag is full
		return false;

	m_bag.emplace_back(std::move(obj)); // put item in the bag
	updateItemPos(); // update the item pos

	if(m_bag.size() == 1)
		currPos = 0;


	ResourceManeger::getInstance().getSound(PICK_ITEM_SD).play();
	ResourceManeger::getInstance().getSound(PICK_ITEM_SD).setLoop(false);
	ResourceManeger::getInstance().getSound(PICK_ITEM_SD).setVolume(100.f);

	return true;
}

inline std::shared_ptr<Items> ItemBag::getItem()
{
	if (m_bag.size() == 0) // when the item bag is  empty
		return nullptr;

	return m_bag[currPos]; // return the curr item that point on
}

inline void ItemBag::moveNextItem()
{
	if (m_bag.size() == 0)
		return;
	++currPos;
	if (currPos == m_bag.size()) // case was in the end
		currPos = 0;

	updatecurPosRect();
}

inline void ItemBag::movPrevItem()
{
	if (m_bag.size() == 0)
		return;

	if (currPos == 0) // case was in the begin
		currPos = m_bag.size() - 1; // point to the end
	else
		--currPos;

	updatecurPosRect();
}

inline void ItemBag::removeCurrPosItem()
{
	m_bag.erase(m_bag.begin() + currPos);
	if (currPos != 0)
		--currPos;

	updateItemPos(); // update the item pos
}

inline void ItemBag::updateItemPos()
{
	size_t base = 0;
	for (auto &x : m_bag)
	{
		(*x).setPosition(static_cast<float>(base * TILESIZE), 0);
		base++;
	}
	

}


inline void ItemBag::updatecurPosRect()
{
	if (m_bag.size() == 0)
		curPosRect.setPosition(itemsRect.getPosition());
	else
		curPosRect.setPosition((m_bag[currPos])->getPosition());
}