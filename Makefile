.SUFFIXES:
.PRECIOUS: %.o
.PHONY: all compile checkstyle clean format

CXX = clang++ -Wall -std=c++17 -fsanitize=address
INCLUDE_DIR = ./deps/include/
LIB_DIR = ./deps/lib/linux/
LIBS = -L$(LIB_DIR) -lraylib

# Source and header files
SOURCES := ./src/main.cpp ./src/application.cpp ./src/game.cpp ./src/player.cpp ./src/asset_manager.cpp ./src/level.cpp ./src/main_menu.cpp
HEADERS := ./src/application.h ./src/game.h ./src/player.h ./src/asset_manager.h ./src/level.h ./src/menu.h ./src/main_menu.h
OBJECTS := $(SOURCES:.cpp=.o)
MAIN_BINARY = main

all: compile checkstyle

compile: $(MAIN_BINARY)

$(MAIN_BINARY): $(OBJECTS)
	$(CXX) -I$(INCLUDE_DIR) $(OBJECTS) -o $@ $(LIBS)

%.o: %.cpp
	$(CXX) -I$(INCLUDE_DIR) -c $< -o $@

checkstyle:
	clang-format --dry-run -Werror $(HEADERS) $(SOURCES)

clean:
	rm -f $(MAIN_BINARY)
	rm -f $(OBJECTS)

format:
	clang-format-14 -i $(HEADERS) $(SOURCES)
