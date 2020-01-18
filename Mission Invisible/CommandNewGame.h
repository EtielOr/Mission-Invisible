#pragma once

#include "Command.h"
#include "LevelController.h"

// command to restart the level

class CommandNewGame : public Command
{
public:
	CommandNewGame(LevelController &obj) : m_obj(obj) {};

	virtual void execute() { m_obj.newGame(); };

private:
	LevelController & m_obj;
};

