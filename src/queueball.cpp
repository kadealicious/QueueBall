#include<iostream>
#include"queueball.hpp"


QueueBall::QueueBall()
{
	this->currentCommandID = 0;
};

int QueueBall::GetCommandIndex(unsigned int commandID, int low, int high)
{
	if(low < 0 || high < 0)
		{ low = 0; high = this->commands.size(); }
	if(this->commands.size() < 1)
		{ /* std::cout << "ERROR: No commands are currently bound; can't search!" << std::endl; */ return -1; }

	unsigned int middleIndex = (low + high) / 2;
	unsigned int middleCommandID = this->commands.at(middleIndex).commandID;

	if(commandID > middleCommandID)
	{
		if((low + 1) == high)
		{
			// std::cout << "ERROR: Command w/ ID " << commandID << " was likely unbound!" << std::endl;
			return -1;
		}
		return this->GetCommandIndex(commandID, middleIndex, high);
	}
	else if(commandID < middleCommandID)
	{
		if((high - 1) == low)
		{
			// std::cout << "ERROR: Command w/ ID " << commandID << " was likely unbound!" << std::endl;
			return -1;
		}
		return this->GetCommandIndex(commandID, low, middleIndex);
	}
	else if(commandID == middleCommandID)
	{
		return middleIndex;
	}

	// std::cout << "ERROR: No command found w/ ID " << commandID << "!" << std::endl;
	return -1;
}

QbResult QueueBall::BindCommand(unsigned int& commandID, void (*commandFnPtr)())
{
	qbCommand command;
	command.commandID = this->currentCommandID;
	command.commandFnPtr = commandFnPtr;
	command.argCount = 0;
	this->commands.push_back(command);

	commandID = this->currentCommandID;
	// std::cout << "Bound command w/ ID " << commandID << "!" << std::endl;
	this->currentCommandID++;
	return qbOkay;
}

QbResult QueueBall::BindCommand(unsigned int& commandID, void (*commandFnPtr)(void*), unsigned int argCount)
{
	qbCommand command;
	command.commandID = this->currentCommandID;
	command.commandFnPtrWithArg = commandFnPtr;
	command.argCount = argCount;
	this->commands.push_back(command);

	commandID = this->currentCommandID;
	// std::cout << "Bound command w/ ID " << commandID << "!" << std::endl;
	this->currentCommandID++;
	return qbOkay;
}

QbResult QueueBall::UnbindCommand(unsigned int commandID)
{
	int commandIndex = this->GetCommandIndex(commandID, -1, -1);
	if(commandIndex >= 0)
	{
		commands.erase(commands.begin() + commandIndex);
		// std::cout << "Unbound command w/ ID " << commandID << "!" << std::endl;
		return qbOkay;
	}
	else
	{
		// std::cout << "ERROR: Failed to unbind command w/ ID " << commandID << "!" << std::endl;
		return qbCommandNotFound;
	}

	return qbFail;
}

QbResult QueueBall::RecordCommand(unsigned int commandID)
{
	int commandIndex = this->GetCommandIndex(commandID, -1, -1);
	if(commandIndex >= 0)
	{
		/* Create a new command-argument pair on the heap for scope, then point the command at 
			this->commands to reduce execution time (no searching required). */
		qbCommandArgumentPair* newPair = (qbCommandArgumentPair*)malloc(sizeof(qbCommandArgumentPair));
		newPair->command = &commands.at(commandIndex);
		commandDeque.push_back(newPair);
		
		// std::cout << "Command w/ ID " << commandID << " queued successfully!" << std::endl;
		return qbOkay;
	}
	else
	{
		// std::cout << "ERROR: Failed to record command w/ ID " << commandID << "!" << std::endl;
		return qbCommandNotFound;
	}

	return qbFail;
}

QbResult QueueBall::RecordCommand(unsigned int commandID, void* commandArgs)
{
	int commandIndex = this->GetCommandIndex(commandID, -1, -1);
	if(commandIndex >= 0)
	{
		/* Create a new command-argument pair on the heap for scope, then point the command at 
			this->commands to reduce execution time (no searching required). */
		qbCommandArgumentPair* newPair = (qbCommandArgumentPair*)malloc(sizeof(qbCommandArgumentPair));
		newPair->command = &commands.at(commandIndex);
		newPair->args = commandArgs;
		
		commandDeque.push_back(newPair);
		// std::cout << "Command w/ ID " << commandID << " and " << newPair->command->argCount << " args queued successfully!" << std::endl;
		return qbOkay;
	}
	else
	{
		// std::cout << "ERROR: Failed to record command w/ ID " << commandID << "!" << std::endl;
		return qbCommandNotFound;
	}

	return qbOkay;
}

QbResult QueueBall::ExecuteCommands()
{
	/* unsigned int commandCount = this->commandDeque.size();

	if(commandCount > 0)
		{ std::cout << "Executing " << commandCount << " command(s) in queue..." << std::endl; }
	else
		{ std::cout << "ERROR: No commands queued for execution!" << std::endl; } */

	while(this->commandDeque.size() > 0)
	{
		// We pull from the front of the deque to execute commands.
		qbCommandArgumentPair* currentCommand = commandDeque.front();
		// std::cout << "-Executing command w/ ID " << currentCommand->command->commandID << ": " << std::endl;
		
		// Execute the command with appropriate arguments (if any).
		if(commandDeque.front()->command->argCount < 1)
		{
			currentCommand->command->commandFnPtr();
		}
		else
		{
			// TODO: Make >1 arguments work so you don't need to use a struct to pass the arguments.
			currentCommand->command->commandFnPtrWithArg(currentCommand->args);
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
	int commandIndex = this->GetCommandIndex(commandID, -1, -1);
	if(commandIndex >= 0)
	{
		std::cout << "Command " << commandIndex << ": Command ID " << this->commands.at(commandID).commandID;
		std::cout << " w/ " << this->commands.at(commandID).argCount << " args." << std::endl;
	}
	else
	{
		std::cout << "ERROR: Failed to print details for command w/ ID " << commandID << "!" << std::endl;
	}
}

void QueueBall::ListQueuedCommands()
{
	for(unsigned int i = 0; i < this->commandDeque.size(); i++)
	{
		this->PrintCommandDetails(this->commandDeque.at(i)->command->commandID);
	}
}