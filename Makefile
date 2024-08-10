.SUFFIXES:
.PRECIOUS: %.o
.PHONY: all compile checkstyle test clean format

CXX = clang++ -Wall -std=c++17 -fsanitize=address
INCLUDE_DIR = ./deps/include/
LIB_DIR = ./deps/lib/linux/
LIBS = -L$(LIB_DIR) -lraylib
TESTLIBS = -lgtest -lgtest_main -lpthread

# Source and header files
SOURCES := ./src/main.cpp ./src/application.cpp ./src/game.cpp ./src/player.cpp ./src/asset_manager.cpp ./src/level.cpp ./src/main_menu.cpp
HEADERS := ./src/application.h ./src/game.h ./src/player.h ./src/asset_manager.h ./src/level.h ./src/menu.h ./src/main_menu.h
OBJECTS := $(SOURCES:.cpp=.o)
MAIN_BINARY = main

# Test source and object files
TEST_SOURCES := ./src/test/game_test.cpp ./src/test/mock_game.cpp ./src/test/mock_player.cpp ./src/test/mock_main_menu.cpp ./src/test/mock_level.cpp
TEST_OBJECTS := $(TEST_SOURCES:.cpp=.o)
TEST_BINARY = test_bin

all: compile checkstyle test

compile: $(MAIN_BINARY)

test: $(TEST_BINARY)
	./$(TEST_BINARY)

$(MAIN_BINARY): $(OBJECTS)
	$(CXX) -I$(INCLUDE_DIR) $(OBJECTS) -o $@ $(LIBS)

$(TEST_BINARY): $(TEST_OBJECTS)
	$(CXX) -I$(INCLUDE_DIR) $(TEST_OBJECTS) -o test_bin $(LIBS) $(TESTLIBS)

%.o: %.cpp
	$(CXX) -I$(INCLUDE_DIR) -c $< -o $@

checkstyle:
	clang-format --dry-run -Werror $(HEADERS) $(SOURCES)

clean:
	rm -f $(MAIN_BINARY)
	rm -f $(TEST_BINARY)
	rm -f $(OBJECTS)
	rm -f $(TEST_OBJECTS)

format:
	clang-format-14 -i $(HEADERS) $(SOURCES)
