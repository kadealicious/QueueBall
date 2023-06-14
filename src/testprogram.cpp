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
    unsigned int printStringAsArgumentCommandID;
    std::string testString = "This string is a test string!";
    unsigned int printCStringAsArgumentCommandID;
    typedef struct cString { const char* str; uint32_t strLength; } cStringArgs;
    cStringArgs testArgs = { "My name is Jonas\0", 17};

    queueBall.BindCommand(printHelloWorldCommandID, &PrintHelloWorld, 0);                  // Test binding with 0 args.
    queueBall.BindCommand(printStringAsArgumentCommandID, &PrintStringAsArgument, 1);      // Test binding with 1 arg.
    queueBall.BindCommand(printCStringAsArgumentCommandID, &PrintCStringAsArgument, 2);    // Test binding with 2 args.
    
    queueBall.RecordCommand(printHelloWorldCommandID, nullptr);                        // Test execution with 0 args.
    queueBall.RecordCommand(printStringAsArgumentCommandID, (void*)(&testString));    // Test execution with 1 arg.
    queueBall.RecordCommand(printCStringAsArgumentCommandID, (void*)(&testArgs));     // Test execution with 2 args.
    queueBall.RecordCommand(printStringAsArgumentCommandID, nullptr);                  // Test execution with incorrect(-) number of args.
    queueBall.RecordCommand(printStringAsArgumentCommandID, (void*)(&testArgs));      // Test execution with incorrect(+) number of args.

    queueBall.UnbindCommand(printStringAsArgumentCommandID);                           // Test unbinding.
    queueBall.RecordCommand(printStringAsArgumentCommandID, (void*)(&testString));    // Test execution after unbinding.

    return 0;
}