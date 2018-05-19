FLAGS = -std=c++17 \
		-Wall   \
		-Wextra \
		-Werror

SOURCE = $(shell find source -name '*.cpp')
OUTPUT = Depengine.run

all: $(OUTPUT)

$(OUTPUT): $(SOURCE)
	@echo "Compiling..."
	@g++ $(FLAGS) $^ -o $@

run: $(OUTPUT)
	@echo "Running..."
	@./$<

clean:
	@echo "Cleaning..."
	@rm -f $(OUTPUT)
