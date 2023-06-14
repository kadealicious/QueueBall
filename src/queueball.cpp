#include<iostream>
#include"queueball.hpp"


QbResult QueueBall::BindCommand(unsigned int& commandID, void (*commandFnPtr)())
{
	static unsigned int currentCommandID = 0;

	qbCommand command;
	command.commandID = currentCommandID;
	command.commandFnPtr = commandFnPtr;
	command.argCount = 0;
	this->commands.push_back(command);

	commandID = currentCommandID;
	std::cout << "Bound command w/ ID " << commandID << "!" << std::endl;

	currentCommandID++;
	return qbOkay;
}

QbResult QueueBall::BindCommand(unsigned int& commandID, void (*commandFnPtr)(void*), unsigned int argCount)
{
	static unsigned int currentCommandID = 0;

	qbCommand commandPair;
	commandPair.commandID = currentCommandID;
	commandPair.commandFnPtrArgs = commandFnPtr;
	commandPair.argCount = argCount;

	this->commands.push_back(commandPair);

	commandID = currentCommandID;
	std::cout << "Bound command w/ ID " << commandID << "!" << std::endl;
	currentCommandID++;
	return qbOkay;
}

QbResult QueueBall::UnbindCommand(unsigned int commandID)
{
	for(unsigned int i = 0; i < this->commands.size(); i++)
	{
		if(commands.at(i).commandID == commandID)
		{
			commands.erase(commands.begin() + i);
			std::cout << "Unbound command w/ ID " << commandID << "!" << std::endl;
			return qbOkay;
		}
	}

	std::cout << "ERROR: Failed to unbind command w/ ID " << commandID << "!" << std::endl;
	return qbCommandNotFound;
}

QbResult QueueBall::RecordCommand(unsigned int commandID)
{
	// Determine the correct command to record.
	// TODO: Make this use a binary search for < O(N) performance.
	for(unsigned int i = 0; i < this->commands.size(); i++)
	{
		if(commands.at(i).commandID == commandID)
		{
			/* Create a new command-argument pair on the heap for scope, then point the command at 
				this->commands to reduce execution time (no searching required). */
			qbCommandArgumentPair* newPair = (qbCommandArgumentPair*)malloc(sizeof(qbCommandArgumentPair));
			newPair->command = &commands.at(i);
			commandDeque.push_back(newPair);
			
			std::cout << "Command w/ ID " << commandID << " queued successfully!" << std::endl;
			return qbOkay;
		}
	}

	return qbOkay;
}

QbResult QueueBall::RecordCommand(unsigned int commandID, void* commandArgs)
{
	// Determine the correct command to record.
	// TODO: Make this use a binary search for < O(N) performance.
	for(unsigned int i = 0; i < this->commands.size(); i++)
	{
		if(commands.at(i).commandID == commandID)
		{
			qbCommandArgumentPair* newPair = (qbCommandArgumentPair*)malloc(sizeof(qbCommandArgumentPair));
			newPair->command = &commands.at(i);
			newPair->args = commandArgs;
			
			commandDeque.push_back(newPair);
			std::cout << "Command w/ ID " << commandID << " queued successfully!" << std::endl;
			return qbOkay;
		}
	}

	return qbOkay;
}

QbResult QueueBall::ExecuteCommands()
{
	unsigned int commandCount = this->commandDeque.size();

	if(commandCount > 0)
		{ std::cout << "Executing " << commandCount << " command(s) in queue..." << std::endl; }
	else
		{ std::cout << "WARNING: No commands queued for execution!" << std::endl; }

	while(this->commandDeque.size() > 0)
	{
		// We pull from the front of the queue to execute commands.
		qbCommandArgumentPair* currentCommand = commandDeque.front();
		std::cout << "Executing command w/ ID " << currentCommand->command->commandID << ": ";
		
		// Execute the command with appropriate arguments (if any).
		if(commandDeque.front()->command->argCount < 1)
		{
			currentCommand->command->commandFnPtr();
		}
		else
		{
			// TODO: Do something.
		}

		// Remove command from deque and free its memory.
		free(commandDeque.front());
		commandDeque.pop_front();
	}

	return qbOkay;
}

void QueueBall::PrintCommandDetails(unsigned int commandID)
{
	// Figure out which command pointer we are talking about.
	// TODO: Make this use a binary search for < O(N) performance.
	void *commandFnPtr;
	for(unsigned int i = 0; i < this->commands.size(); i++)
	{
		if(commands.at(i).commandID == commandID)
		{
			commandFnPtr = &(this->commands.at(i).commandFnPtr);
		}
	}

	std::cout << "Command w/ ID " << this->commands.at(commandID).commandID;
	std::cout << " will execute function " << commandFnPtr;
	std::cout << " with " << this->commands.at(commandID).argCount << " args." << std::endl;
}