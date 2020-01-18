#include "CommandMap.h"

CommandMap& CommandMap::getInstace()
{
	static CommandMap cmdMap; // single ton

	return cmdMap;
}

bool CommandMap::registerCommand(const std::string & cmdName, std::unique_ptr<Command> && cmd)
{
	m_map.emplace(cmdName, std::move(cmd));

	return true;
}

bool CommandMap::unregisterCommand(const std::string &cmdName)
{
	m_map.erase(cmdName);


	return true;
}

void CommandMap::doCommand(const std::string &cmdName)
{
	auto currCmd = m_map.find(cmdName);

	if (currCmd == m_map.end())
		throw(std::runtime_error("unkown cmd"));

	currCmd->second->execute(); // do the cmd


}

