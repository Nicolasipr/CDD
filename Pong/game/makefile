CXX=g++
CXXFLAGS= -std=c++11 -Wall -Wextra -lncurses
EXPORT=-o pongGame
all:
	$(CXX) $(CXXFLAGS) ../main.cpp Board.cpp Player.cpp Menu.cpp $(EXPORT)

# pongGame: main.o Board.o Player.o Menu.o
# 	g++ -std=c++11 -Wall -Wextra -lncurses main.o Board.o Player.o Menu.o -o pongGame
#
# main.o: main.cpp
# 	g++ -c main.cpp -o main.o
#
# Board.o: Board.cpp
# 	g++ Board.cpp -o Board.o
#
# Player.o: Player.cpp
# 	g++ Player.cpp -o Player.o
#
# Menu.o: Menu.cpp
# 	g++ Player.cpp -o Player.o

clean:
	rm *.o pongGame