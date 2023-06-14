#include<iostream>
#include"queueball.hpp"


QbResult QueueBall::BindCommand(unsigned int& commandID, void (*commandFnPtr)(), unsigned int argCount)
{
	static unsigned int currentCommandID = 0;

	qbCommand commandPair;
	commandPair.commandID = currentCommandID;
	commandPair.commandFnPtr = commandFnPtr;
	commandPair.argCount = argCount;

	this->commands.push_back(commandPair);

	commandID = currentCommandID;
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
			return qbOkay;
		}
	}

	return qbCommandNotFound;
}

// TODO: Use any other algorithm that is faster than O(N) here.
QbResult QueueBall::RecordCommand(unsigned int commandID, void* commandArgs)
{
	for(unsigned int i = 0; i < this->commands.size(); i++)
	{
		if(commands.at(i).commandID == commandID)
		{
			qbCommandArgumentPair* newPair = (qbCommandArgumentPair*)malloc(sizeof(qbCommandArgumentPair));
			newPair->commandFnPtr = commands.at(i).commandFnPtr;
			newPair->args = commandArgs;
			
			commandDeque.push_back(newPair);
			return qbOkay;
		}
	}

	return qbOkay;
}

QbResult QueueBall::ExecuteCommands()
{
	while(this->commandDeque.size() > 0)
	{
		qbCommandArgumentPair* currentCommand = commandDeque.front();
		
		// TODO: Call function with arguments here.
		// currentCommand->commandFnPtr(currentCommand->args);

		free(commandDeque.front());
		commandDeque.pop_front();
	}

	return qbOkay;
}

void QueueBall::PrintCommandDetails(unsigned int commandID)
{
	std::cout << "Command w/ ID " << this->commands.at(commandID).commandID;
	std::cout << " will execute function " << &(this->commands.at(commandID).commandFnPtr);
	std::cout << " with " << this->commands.at(commandID).argCount << " args." << std::endl;
}