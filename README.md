# Preview

Main menu SDL:
![menu1](./ressources/sdl.png)

Main menu nCurses:
![menu2](./ressources/ncurses.png)

# Arcade

Arcade is a **gaming platform**: a program that lets the user choose a game to play and keeps a register of player scores.
To be able to deal with the elements of your gaming plate-form at run-time, your graphic libraries and your games
must be implemented as dynamic libraries, loaded at run-time.

Each GUI available for the program must be used as a shared
library that will be loaded and used dynamically by the main
program.

## Games

Here is the list of games we have implemented:

### Nibbler

Nibbler is a simple arcade video game released in 1982.
Its concept has spread mainly thanks to the cult game Snake.
Nibbler itself was inspired by another great classic: Blockade, itself inspired from Tron Light Cycle.
The simplicity and addictiveness of Snake made it available on almost every existing platform under various
names.
As you may know, Snake is about moving a snake around a map.
The snake is represented by sections and must eat food in order to grow.
The game is over when the head of the snake hits an edge of the map or one of the sections.
The goal of the game is to make the snake as long as possible.

### Pacman

Pacman is an arcade video game released in 1980.
The goal is to explore a maze in order to eat all the “pacgums” in it while avoiding ghosts.
Some “pacgums” let the player invert roles: Pacman can, for a short period of time, eat ghosts instead of
being eaten.
Eaten ghosts do not disappear: their eyes head back to an unaccessible zone in the middle of the maze.
They change back to normal ghosts after a short period.

### SolarFox

The player's task is to pilot a starship through a series of squared solar cell matrixes inside a rack.
While capturing the cells the player must dodge waves of fireballs that are being thrown by Sentinels.
These Sentinels move continuously along the perimeter of each cell formation.
When an entire field of squares is completed (by flying through each square), the game advances to the next rack.
The faster a matrix is cleared, the more points are received.

## Graphical libs

Here is the list of libs we have implemented:

### SFML

SFML provides a simple interface to the various components of your PC, to ease the development of games and multimedia applications. It is composed of five modules: system, window, graphics, audio and network.

### SDL

Simple DirectMedia Layer is a cross-platform development library designed to provide low level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D.

### NCurses

ncurses (new curses) is a programming library providing an application programming interface (API) that allows the programmer to write text-based user interfaces in a terminal-independent manner. It is a toolkit for developing "GUI-like" application software that runs under a terminal emulator. It also optimizes screen changes, in order to reduce the latency experienced when using remote shells.
