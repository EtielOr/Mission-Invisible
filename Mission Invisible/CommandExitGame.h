#pragma once

#include "Command.h"
#include "LevelController.h"

// command to restart the level

class CommandExitGame : public Command
{
public:
	CommandExitGame(LevelController &obj) : m_obj(obj) {};

	virtual void execute() { m_obj.exit(); };

private:
	LevelController & m_obj;
};
