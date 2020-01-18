#pragma once

#include "Command.h"
#include "LevelController.h"

// command to restart the level

class CommandNextLevel : public Command
{
public:
	CommandNextLevel(LevelController &obj) : m_obj(obj) {};

	virtual void execute() { m_obj.nextLevel(); };

private:
	LevelController & m_obj;
};
