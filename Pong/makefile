CXX=g++
CXXFLAGS= -std=c++11 -Wall -Wextra
EXPORT=-o pongGame
all:
	$(CXX) $(CXXFLAGS) main.cpp game/Game.cpp game/Board.cpp game/Player.cpp game/Menu.cpp  $(EXPORT)

clean:
	rm *.o pongGame