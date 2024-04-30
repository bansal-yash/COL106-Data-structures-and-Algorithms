# makefile for compiling all C++ files

# Compiler Version
CC = g++

# Compiler Flags
CFLAGS = -Wall -g -std=c++11

# Target
TARGET = qna_tool

# Object Files
OBJ = qna_tool.o Node.o tester.o dict.o search.o

# Header Files
HEADER = qna_tool.h Node.h dict.h search.h

# cpp Files
CPP = qna_tool.cpp Node.cpp tester.cpp dict.cpp search.cpp

# Compile
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)
	rm -f $(OBJ)

# Object Files
qna_tool.o: qna_tool.cpp
	$(CC) $(CFLAGS) -c qna_tool.cpp

Node.o: Node.cpp
	$(CC) $(CFLAGS) -c Node.cpp

# Tester
tester.o: tester.cpp
	$(CC) $(CFLAGS) -c tester.cpp

# Dictionary
dict.o: dict.cpp
	$(CC) $(CFLAGS) -c dict.cpp

# Search
search.o: search.cpp
	$(CC) $(CFLAGS) -c search.cpp

# Clean
clean:
	rm -f $(OBJ) $(TARGET) *~

# Run
run:
	./$(TARGET)

# debug
debug:
	gdb ./$(TARGET)