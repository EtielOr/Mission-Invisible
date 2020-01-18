#pragma once

#include "Command.h"
#include "LevelController.h"

// command to restart the level

class CommandRestartLevel : public Command
{
public:
	CommandRestartLevel(LevelController &obj) : m_obj(obj) {};

	virtual void execute() { m_obj.restart(); };

private:
	LevelController & m_obj;
};