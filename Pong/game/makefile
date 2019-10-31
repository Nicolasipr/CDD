#Makefile for Pong
##

SHELL=/bin/sh
DEBUG_OPTIONS=-std=c++11 -ggdb3 -Wall -Wextra -lncurses -o pong

SRCDIR=.
SOURCES_= main.cpp Board.cpp Player.cpp Menu.cpp
SOURCES=$(addprefix $(SRCDIR),$(SOURCES_))

INCLUDES_=ncurses
INCLUDES=$(addprefix -l,$(INCLUDES_))
MY_INCLUDES=./includes/

EXE=pong


all:
	$(CC) $(INCLUDES) -I$(MY_INCLUDES) $(SOURCES) -o $(EXE)

debug:
	$(CC) $(DEBUG_OPTIONS) $(INCLUDES) -I$(MY_INCLUDES) $(SOURCES) -o $(EXE)
S