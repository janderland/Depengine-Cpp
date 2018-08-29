DIRS=treet depengine
SOURCES=$(shell find $(DIRS) -name '*.cpp')
CXXFLAGS=-std=c++17 -Wall -Wextra -Werror -I. -lboost_system -lboost_filesystem
OUTPUT=treet.run

all: $(OUTPUT)

run: $(OUTPUT)
	@./$(OUTPUT)

$(OUTPUT): $(SOURCES)
	@$(CXX) $(CXXFLAGS) $^ -o $@
