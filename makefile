#sheblamo
CC=g++
CFLAGS=-Wall -Werror -std=c++0x
#
WKDIR=($(HOME)/programs/csci-2270/project5/)

all: program

program: Assignment6.cpp
	$(CC) $(CFLAGS) Assignment6.cpp MovieTree.cpp MovieTree.h -o Assignment6.o

clean:
	rm *o Assignment6
