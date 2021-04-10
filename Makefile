##
## EPITECH PROJECT, 2021
## arcade
## File description:
## Makefile
##

all:	games graphicals core

core:
	$(MAKE) -C src/games_libs clean
	$(MAKE) -C src/core

core_debug:
	$(MAKE) -C src/core debug

games:
	$(MAKE) -C src/core clean
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