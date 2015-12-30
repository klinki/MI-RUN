# Declaration of variables
CC = g++
CC_FLAGS = -w -m32 -std=c++14 -D_DEBUG

# File names
EXEC = jvm
SOURCES := $(shell find $(SOURCEDIR) -name '*.cpp')
OBJECTS = $(SOURCES:.cpp=.o)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)

