# Declaration of variables
# CXX = g++
CXX_FLAGS = -w -m32 -std=c++14

# File names
EXEC = jvm
SOURCEDIR = .
SOURCES := $(shell find $(SOURCEDIR) -name '*.cpp')
OBJECTS = $(SOURCES:.cpp=.o)

# Main target
main: $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC)

# To obtain object files
%.o: %.cpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)

debug: CXX_FLAGS +=  -D_DEBUG -g
debug: main
	
build: 
	main
	
all: 
	clean
	main
