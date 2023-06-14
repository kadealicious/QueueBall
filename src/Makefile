CCFLAGS = -Wall -MMD -m64 -std=c++11
CC = g++
CCLIBS = -lmingw32

all: app

testprogram.o: testprogram.cpp

queueball.o: queueball.cpp
	$(CC) $(CCFLAGS) -c $^ -o $@

app: testprogram.o queueball.o
	$(CC) $(CCFLAGS) -o $@ $^ $(CCLIBS)

.PHONY: app