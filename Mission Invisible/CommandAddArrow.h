#pragma once


#include "Command.h"
#include "LevelController.h"

// command to restart the level

class CommandAddArrow: public Command
{
public:
	CommandAddArrow(LevelController &obj) : m_obj(obj) {};

	virtual void execute() { m_obj.addArrow(); };

private:
	LevelController & m_obj;
};
