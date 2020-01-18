#pragma once
#include "MapObject.h"

class Treasure : public MapObject
{
public:
	Treasure(const int &x, const int &y);

	virtual void collideWith(DynamicObject& obj);
	virtual void collideWith(const Wall&) {};
	virtual void collideWith(const Floor&) {};
	virtual void collideWith(Door&) {};
	virtual void collideWith(const Treasure&) {};

	virtual bool openDoor(Door& obj);
	virtual bool openDoor(Key& obj);
	virtual bool openDoor(std::shared_ptr<Items> &);

	virtual bool isPassAble();



	virtual sf::FloatRect getGlobalBounds()  const; // return Sprite bounds
	virtual sf::Vector2f getPosition() const;  // return Sprite pos

	virtual void loadTexture(const std::string &name); // get what texture to load and load it




private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // to draw the map
	static bool isRegisterFactory; // to register in the factor


};


