CC      = g++
CFLAGS  = -std=c++17 -Wall -Wextra -Wpedantic -Werror -g
LIBS = -lncurses -lfmt -pthread -lsfml-graphics -lsfml-window -lsfml-system

SOURCES := $(wildcard *.cpp stepperControl/*.cpp)
FAKESOURCES := $(shell ls *.cpp stepperControl/*.cpp | grep -v gpio.cpp)

BINARY = els

.PHONY: all clean fake

all: $(BINARY)


$(BINARY): $(SOURCES)
	$(CC) -O3 $(CFLAGS) $(SOURCES) -o $(BINARY) $(LIBS) -lpigpio
	ctags -R --c++-kinds=+p --fields=+iaS

# Make binary without need for pigpio lib for testing UI
fake: $(SOURCES)
	$(CC) -DFAKE $(CFLAGS) $(FAKESOURCES) -o $(BINARY) $(LIBS)
	ctags -R --c++-kinds=+p --fields=+iaS
	cppcheck -q $(SOURCES)

clean:
	rm -f $(BINARY)
	rm -f tags
