##
## EPITECH PROJECT, 2021
## arcade
## File description:
## Makefile
##

CC	=	g++

TARGET	=	arcade

CPPFLAGS	=	-W -Wall -Wextra -std=c++17

LDFLAGS	=	-ldl

SRC	=	$(wildcard src/core/*.cpp)	\

OBJ	=	$(SRC:.cpp=.o)

all:	core games graphicals

core:	$(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

games:
	$(MAKE) -C src/games_libs

graphicals:
	$(MAKE) -C src/graphicals_libs

debug:	CPPFLAGS += -g3

debug:	all

clean:
	$(RM) $(OBJ)
	$(MAKE) -C src/games_libs clean
	$(MAKE) -C src/graphicals_libs clean

fclean:	clean
	$(RM) $(TARGET)
	$(MAKE) -C src/games_libs fclean
	$(MAKE) -C src/graphicals_libs fclean

re:	fclean all