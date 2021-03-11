##
## EPITECH PROJECT, 2021
## arcade
## File description:
## Makefile
##

CC	=	g++

TARGET	=	../../../lib/arcade_sdl2.so

CPPFLAGS	=	-W -Wall -Wextra -std=c++17 -fPIC -lSDL2_ttf

LDFLAGS	=	-shared -lSDL2 -L../../../ressources

SRC	=	$(wildcard *.cpp)	\
		../../core/AGraphicalModule.cpp

OBJ	=	$(SRC:.cpp=.o)

all:	$(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

debug:	CPPFLAGS += -g3

debug:	all

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(TARGET)

re:	fclean all