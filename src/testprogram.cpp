#include<iostream>
#include<cstdint>
#include<string>
#include"queueball.hpp"


void PrintHelloWorld()
	{ std::cout << "Hello world!" << std::endl; }
void PrintArgumentAsString(std::string str)
	{ std::cout << str << std::endl; }

struct CStringArgs { const char* cStr; unsigned int cStrLength; };
void PrintArgumentAsCString(CStringArgs args)
	{ printf("%i: %s\n", args.cStrLength, args.cStr); }

int main(int argc, char* argv[])
{
	QueueBall queueBall;
	
	unsigned int printHelloWorldCommandID;
	unsigned int PrintArgumentAsStringCommandID;
	std::string testString = "My name is Jonas, ";
	unsigned int PrintArgumentAsCStringCommandID;
	CStringArgs testStruct;
	testStruct.cStr = "I'm carrying the wheel!\0";
	testStruct.cStrLength = 23;
	
	queueBall.BindCommand(printHelloWorldCommandID, PrintHelloWorld);								// Test binding with 0 args.
	queueBall.BindCommand(PrintArgumentAsStringCommandID, (qbFnPtr)PrintArgumentAsString, 1);		// Test binding with 1 arg.
	queueBall.BindCommand(PrintArgumentAsCStringCommandID, (qbFnPtr)PrintArgumentAsCString, 2);		// Test binding with 2 args.
	
	queueBall.PrintCommandDetails(printHelloWorldCommandID);
	queueBall.PrintCommandDetails(PrintArgumentAsStringCommandID);
	queueBall.PrintCommandDetails(PrintArgumentAsCStringCommandID);

	queueBall.RecordCommand(printHelloWorldCommandID);									// Test record with 0 args.
	queueBall.RecordCommand(PrintArgumentAsStringCommandID, (qbArgPtr)(&testString));	// Test record with 1 arg.
	queueBall.RecordCommand(PrintArgumentAsCStringCommandID, (qbArgPtr)(&testStruct));	// Test record with 2 args.

	queueBall.ListQueuedCommands();

	queueBall.ExecuteCommands();	// Test regular execution.
	queueBall.ExecuteCommands();	// Test double execution.

	queueBall.RecordCommand(printHelloWorldCommandID);	// Test recording after execution.
	queueBall.ExecuteCommands();						// FInal execution test.

	return 0;
}