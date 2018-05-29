.PHONY: clean
CC=g++
CXXFLAGS=-std=c++17
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lm
all: *.o
	$(CC) $(CXXFLAGS) $(LIBS) *.cpp
%.o: %.cpp
	$(CC) $(CXXFLAGS) $(LIBS) -c $^

debug: CXXFLAGS += -g
debug: all

clean: 
	-rm *.o
#	-rm *.gch
	-rm a.out 
