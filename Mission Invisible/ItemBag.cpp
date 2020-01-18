#include "ItemBag.h"

ItemBag::ItemBag() :
	itemsRect(sf::Vector2f(static_cast<float>(TILESIZE*BAG_SIZE), static_cast<float>(TILESIZE))),
	curPosRect(sf::Vector2f(static_cast<float>(TILESIZE), static_cast<float>(TILESIZE)))
	, currPos(0)
{
	itemsRect.setFillColor(sf::Color(255, 255, 255, 128));
	itemsRect.setOutlineColor(sf::Color(255, 215, 0, 100));
	itemsRect.setOutlineThickness(-1.25f);
	curPosRect.setOutlineColor(sf::Color(255, 215, 0, 100));
	curPosRect.setOutlineThickness(1.f);

}



void ItemBag::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(itemsRect);
	target.draw(curPosRect);

	for (auto &x : m_bag)
	{
		target.draw(*x);
	}
}