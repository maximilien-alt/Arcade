##
## EPITECH PROJECT, 2021
## arcade
## File description:
## Makefile
##

CC	=	g++

TARGET	=	../../../lib/arcade_sfml.so

CPPFLAGS	=	-W -Wall -Wextra -std=c++17 -fPIC

SFML = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lsfml-network

LDFLAGS	=	-shared

SRC	=	$(wildcard *.cpp)	\
		../../core/AGraphicalModule.cpp

OBJ	=	$(SRC:.cpp=.o)

all:	$(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS) $(SFML)

debug:	CPPFLAGS += -g3

debug:	all

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(TARGET)

re:	fclean all