#pragma once

#include <map>
#include <memory>
#include "Command.h"
#include "Const.h"


// class that hold command in map to do them with input string



class CommandMap
{
public:
	static CommandMap& getInstace();

	bool registerCommand(const std::string &cmdName, std::unique_ptr<Command> && cmd); // add new cmd
	bool unregisterCommand(const std::string &cmdName); // remove cmd
	void doCommand(const std::string &cmdName); // do the cmd

	CommandMap(const CommandMap&) = delete;
	auto operator=(const CommandMap&) = delete;

private:
	CommandMap() {};

	std::map<std::string, std::unique_ptr<Command> >  m_map; // map to return object
};

