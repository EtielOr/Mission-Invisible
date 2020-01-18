#pragma once

// to do commands


class Command
{
public:
	virtual ~Command() {}
	virtual void execute() = 0;
};