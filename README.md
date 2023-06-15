# QueueBall #

...is a lightweight command queueing system written in C++.  Functions are "bound" to an 
instance of the QueueBall class to later be paired with arguments and queued for execution 
via a command ID.

<br>

**Usage**
- Create an instance of the QueueBall class: ```QueueBall qb;```.
- Create an ```unsigned int``` to hold your function's "command ID".
- Bind the command to its ID with ```qb.BindCommand(commandID, PtrToMyFunction)```.  If your function has arguments, use this syntax: ```qb.BindCommand(commandID, (qbFnPtr)PtrToMyFunction, argumentCount)```.
- To add your command to the queue, call ```qb.RecordCommand(commandID)```.  If your function has arguments, use this syntax: ```qb.RecordCommand(commandID, (qbArgPtr)(&MyArgument))``` OR ```qb.RecordCommand(commandID, (qbArgPtr)(&StructContainingMyArguments))```.
- Execute all recorded commands with ```qb.ExecuteCommands()```.
- To unbind a command, call ```qb.UnbindCommand(commandID)```.

<br>

Created by:	**Kade Samson**
<br>
Github repo:	[github.com/kadealicious/QueueBall](https://github.com/kadealicious/QueueBall)
<br>
- Portfolio:	[kadesamson.com](https://www.kadesamson.com)
- Linkedin:		[@kadesamson](https://www.linkedin.com/in/kadesamson/)
- Github:		[@kadealicious](https://github.com/kadealicious)
- Instagram:	[@kadesamson](https://www.instagram.com/kadesamson/)

<br>

**Technical Notes**
- Each command that is bound is stored in a vector of ```QbCommand``` structs.  When commands are queued, the pointer to each recorded ```QbCommand``` is stored in a vector which also stores the newly specified arguments for the command record.  When the commands are executed, their functions and arguments are then executed sequentially from the queue (implemented as a deque to allow for binary search in ```RecordCommand()```).  Because the command arguments are likely not stored in the same memory as the function being called by the command, depending on how scattered memory is this method may cause quite a few cache misses.
- ```BindCommand()``` & ```UnbindCommand()``` are executed in average O(1) time, ```RecordCommand()``` in average O(log N), and ```ExecuteCommands()``` in average O(N).
- Because ```ExecuteCommands()``` must by nature traverse through each executed command in order, it must take the longest time to execute in theory.
- ```RecordCommand()``` uses a binary search, so I was able to get the search time down to (roughly) O(log N), though the function is quite ugly to look at.
