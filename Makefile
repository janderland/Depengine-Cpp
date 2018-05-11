FLAGS = -std=c++14 \
		-Wall   \
		-Wextra \
		-Werror

SOURCE = $(shell find . -name '*.cpp')
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
