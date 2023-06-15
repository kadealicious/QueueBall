#include<iostream>
#include<cstdint>
#include<string>
#include"queueball.hpp"


void PrintHelloWorld()
{
	std::cout << "Hello world!" << std::endl;
}

void PrintStringAsArgument(std::string str)
{
	std::cout << str << std::endl;
}

void PrintCStringAsArgument(const char* str, unsigned int strLength)
{
	printf("%i: %s\n", strLength, str);
}

int main(int argc, char* argv[])
{
	QueueBall queueBall;

	/*unsigned int testCommandID;
	queueBall.BindCommand(testCommandID, &PrintHelloWorld, 0);
	queueBall.PrintCommandDetails(testCommandID);*/
	
	unsigned int printHelloWorldCommandID;
	unsigned int phwCommandID0;
	unsigned int phwCommandID1;
	unsigned int phwCommandID2;
	unsigned int phwCommandID3;
	// unsigned int printStringAsArgumentCommandID;
	// std::string testString = "This string is a test string!";
	// unsigned int printCStringAsArgumentCommandID;
	// typedef struct cString { const char* str; uint32_t strLength; } cStringArgs;
	// cStringArgs testArgs = { "My name is Jonas\0", 17};

	queueBall.BindCommand(printHelloWorldCommandID, &PrintHelloWorld);						// Test binding with 0 args.
	queueBall.BindCommand(phwCommandID0, &PrintHelloWorld);
	queueBall.BindCommand(phwCommandID1, &PrintHelloWorld);
	queueBall.BindCommand(phwCommandID2, &PrintHelloWorld);
	queueBall.BindCommand(phwCommandID3, &PrintHelloWorld);
	// queueBall.BindCommand(printStringAsArgumentCommandID, &PrintStringAsArgument, 1);	// Test binding with 1 arg.
	// queueBall.BindCommand(printCStringAsArgumentCommandID, &PrintCStringAsArgument, 2);	// Test binding with 2 args.
	
	queueBall.PrintCommandDetails(printHelloWorldCommandID);
	queueBall.PrintCommandDetails(phwCommandID0);
	queueBall.PrintCommandDetails(phwCommandID1);
	queueBall.PrintCommandDetails(phwCommandID2);
	queueBall.PrintCommandDetails(phwCommandID3);

	queueBall.RecordCommand(printHelloWorldCommandID);									// Test record with 0 args.
	// queueBall.RecordCommand(printStringAsArgumentCommandID, (void*)(&testString));	// Test record with 1 arg.
	// queueBall.RecordCommand(printCStringAsArgumentCommandID, (void*)(&testArgs));	// Test record with 2 args.
	// queueBall.RecordCommand(printStringAsArgumentCommandID, nullptr);				// Test record with incorrect(-) number of args.
	// queueBall.RecordCommand(printStringAsArgumentCommandID, (void*)(&testArgs));		// Test record with incorrect(+) number of args.

	queueBall.ExecuteCommands();	// Test regular execution.
	queueBall.ExecuteCommands();	// Test double execution.

	queueBall.UnbindCommand(phwCommandID2);									// Test unbinding.
	queueBall.RecordCommand(phwCommandID2);									// Test Recording after unbinding.
	// queueBall.UnbindCommand(printStringAsArgumentCommandID);						  	// Test unbinding.
	// queueBall.RecordCommand(printStringAsArgumentCommandID, (void*)(&testString));	// Test execution after unbinding.

	queueBall.ExecuteCommands();

	return 0;
}