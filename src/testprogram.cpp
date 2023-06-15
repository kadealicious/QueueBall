#include<iostream>
#include<cstdint>
#include<string>
#include"queueball.hpp"


void PrintHelloWorld()
	{ std::cout << "Hello world!" << std::endl; }
void PrintArgumentAsString(std::string str)
	{ std::cout << str << std::endl; }
void PrintArgumentAsCString(const char* str, unsigned int strLength)
	{ printf("%i: %s\n", strLength, str); }

int main(int argc, char* argv[])
{
	QueueBall queueBall;
	
	unsigned int printHelloWorldCommandID;
	unsigned int PrintArgumentAsStringCommandID;
	std::string testString = "My name is Jonas";
	unsigned int PrintArgumentAsCStringCommandID;
	const char* testCString = "I'm carrying the wheel\0";
	unsigned int cStringLength = 0;

	queueBall.BindCommand(printHelloWorldCommandID, PrintHelloWorld);								// Test binding with 0 args.
	queueBall.BindCommand(PrintArgumentAsStringCommandID, (qbFnPtr)PrintArgumentAsString, 1);		// Test binding with 1 arg.
	queueBall.BindCommand(PrintArgumentAsCStringCommandID, (qbFnPtr)PrintArgumentAsCString, 2);		// Test binding with 2 args.
	
	queueBall.PrintCommandDetails(printHelloWorldCommandID);
	queueBall.PrintCommandDetails(PrintArgumentAsStringCommandID);
	queueBall.PrintCommandDetails(PrintArgumentAsCStringCommandID);

	queueBall.RecordCommand(printHelloWorldCommandID);									// Test record with 0 args.
	queueBall.RecordCommand(PrintArgumentAsStringCommandID, (qbArgPtr)(&testString));	// Test record with 1 arg.
	queueBall.RecordCommand(PrintArgumentAsCStringCommandID, (qbArgPtr)(&testCString, &cStringLength));	// Test record with 2 args.

	queueBall.ListQueuedCommands();

	queueBall.ExecuteCommands();	// Test regular execution.
	queueBall.ExecuteCommands();	// Test double execution.

	queueBall.RecordCommand(printHelloWorldCommandID);	// Test recording after execution.
	queueBall.ExecuteCommands();						// FInal execution test.

	return 0;
}