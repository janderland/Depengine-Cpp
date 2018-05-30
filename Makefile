CXX = g++

FLAGS = -std=c++14 \
        -Wextra \
        -Werror \
        -Wall   \
        -O2     \
        -I.

FLAGS += -lboost_filesystem \
         -lboost_system

TREET = $(shell find treet -name '*.cpp')
DEPENGINE = $(shell find depengine -name '*.cpp')
OUTPUT = treet.run

all: $(OUTPUT)

$(OUTPUT): $(TREET) $(DEPENGINE)
	@echo "Compiling $@..."
	@$(CXX) $(FLAGS) $^ -o $@

run: $(OUTPUT)
	@echo "Running $<..."
	@./$<

clean:
	@echo "Cleaning..."
	@rm -f $(OUTPUT)
