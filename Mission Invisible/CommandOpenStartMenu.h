#pragma once

#include "Command.h"
#include "LevelController.h"

// command to restart the level

class CommandOpenStartMenu : public Command
{
public:
	CommandOpenStartMenu(LevelController &obj) : m_obj(obj) {};

	virtual void execute() { m_obj.openStartMenu(); };

private:
	LevelController & m_obj;
};
