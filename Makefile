CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -Wpedantic -pedantic -std=c++17 -Iinclude
SOURCES = src/main.cpp src/game.cpp src/util.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXEC = StarshipAscension

all: release

release: CXXFLAGS += -O3
release: $(EXEC)

debug: CXXFLAGS += -g
debug: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXEC)
