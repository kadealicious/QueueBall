#ifndef QUEUEBALL_H_
#define QUEUEBALL_H_

#include<vector>
#include<deque>

enum QbResult
{
	qbOkay = 0, 
	qbFail, 
	qbCommandNotFound, 
	qbUnrecognizedCommand, 
	qbCommandException, 
	qbBindFail, 
	qbExecuteFail, 
	qbWTF, 
};

// Used to pair a command ID with its function in memory.
typedef struct qbCommand
{
	unsigned int commandID;
	unsigned int argCount;
	union
	{
		void (*commandFnPtr)();
		void (*commandFnPtrArgs)(void*);
	};
	
	// TODO: Allow user to read previous retval here.
}
qbCommand;

typedef struct qbCommandArgumentPair
{
	qbCommand* command;
	void* args;
}
qbCommandArgumentPair;

class QueueBall
{
	private: 
		std::vector<qbCommand> commands;					// Stores the template command data for each command ID.
		std::deque<qbCommandArgumentPair*> commandDeque;	// Stores pointers to queued commands along with user-specified arguments.
	
	protected: 
		int GetCommandIndex(unsigned int commandID, int low, int high);	// Uses a binary search to find command in list of template commands.
	
	public: 
		QbResult BindCommand(unsigned int& commandID, void (*commandFnPtr)());
		QbResult BindCommand(unsigned int& commandID, void (*commandFnPtr)(void*), unsigned int argCount);
		QbResult UnbindCommand(unsigned int commandID);
		QbResult RecordCommand(unsigned int commandID);
		QbResult RecordCommand(unsigned int commandID, void* commandArgs);	// TODO: Allow the user to dequeue specific command calls.
		QbResult ExecuteCommands();

		void PrintCommandDetails(unsigned int commandID);
};


#endif