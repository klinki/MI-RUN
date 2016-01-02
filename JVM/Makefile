# Declaration of variables
CC = g++
CC_FLAGS = -w -m32 -std=c++14

# File names
EXEC = jvm
SOURCEDIR = .
SOURCES := $(shell find $(SOURCEDIR) -name '*.cpp')
OBJECTS = $(SOURCES:.cpp=.o)

# Main target
main: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)

debug: CC_FLAGS +=  -D_DEBUG -g
debug: main
	
build: 
	main
	
all: 
	clean
	main
