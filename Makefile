CXX = clang++

FLAGS = -std=c++14 \
        -Wextra \
        -Werror \
        -Wall   \
		-O2     \
        -I.

FLAGS += -lboost_filesystem \
         -lboost_system

DEPENGINE = $(shell find depengine -name '*.cpp')
MAKER = $(shell find maker -name '*.cpp')
OUTPUT = Maker.run

all: $(OUTPUT)

$(OUTPUT): $(DEPENGINE) $(MAKER)
	@echo "Compiling $@..."
	@$(CXX) $(FLAGS) $^ -o $@

run: $(OUTPUT)
	@echo "Running $<..."
	@./$<

rund: $(OUTPUT)
	@echo "Running..."
	@lldb ./$<

clean:
	@echo "Cleaning..."
	@rm -f $(OUTPUT)
