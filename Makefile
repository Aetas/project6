#sheblamo

#Same as saying CXX
CC = g++
CPPFLAGS = -Wall -Werror -std=c++0x I
OBJ = main.o functions.o
OUTPUT = Assignment6.o
ODIR = ./bin

vpath = %.h ./include
vpath = %.cpp ./src
#JSON_LIB = -l json
#LIBS = -ljson-c

JSON_C_DIR=/usr
CPPFLAGS += -I$(JSON_C_DIR)/include/json-c
LDFLAGS+= -L$(JSON_C_DIR)/lib -ljson-c

program: $(OBJ)
	$(CC) $(CPPFLAGS) $(OBJ) -o $(ODIR)/$(OUTPUT) $(LDFLAGS)

main.o : Assignment6.cpp MovieTree.h
	$(CC) $(CPPFLAGS) -c main.o $(LDFLAGS)

functions.o : MovieTree.cpp MovieTree.h
	$(CC) $(CPPFLAGS) -c functions.o $(LDFLAGS)

.PHONY : clean
clean :
	rm program $(OBJ)

# Creates a log to keep track of things changed
log : Assignment6.cpp $(OBJ)
	lpt -p $?
	touch log

