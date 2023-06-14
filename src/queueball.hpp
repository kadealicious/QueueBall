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
	void (*commandFnPtr)();
	// TODO: Allow user to read previous retval here.
}
qbCommand;

typedef struct qbCommandArgumentPair
{
	void (*commandFnPtr)();
	void* args;
}
qbCommandArgumentPair;

class QueueBall
{
	private: 
		std::vector<qbCommand> commands;
		std::deque<qbCommandArgumentPair*> commandDeque;
	
	public: 
		QbResult BindCommand(unsigned int& commandID, void (*commandFnPtr)(), unsigned int argCount);
		QbResult UnbindCommand(unsigned int commandID);
		QbResult RecordCommand(unsigned int commandID, void* commandArgs);	// TODO: Allow the user to dequeue specific command calls.
		QbResult ExecuteCommands();

		void PrintCommandDetails(unsigned int commandID);
};


#endif