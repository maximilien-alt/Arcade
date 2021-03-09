##
## EPITECH PROJECT, 2021
## arcade
## File description:
## Makefile
##

all:	core games graphicals

core:
	$(MAKE) -C src/core

games:
	$(MAKE) -C src/games_libs

graphicals:
	$(MAKE) -C src/graphicals_libs

clean:
	$(MAKE) -C src/core clean
	$(MAKE) -C src/games_libs clean
	$(MAKE) -C src/graphicals_libs clean

fclean:	clean
	$(MAKE) -C src/core fclean
	$(MAKE) -C src/games_libs fclean
	$(MAKE) -C src/graphicals_libs fclean

re:	fclean all