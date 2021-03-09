/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** arcade_ncurses
*/

#include "arcade_ncurses.hpp"

Arcade::Graphical_Ncurses::Graphical_Ncurses() : AGraphicalModule()
{
}

Arcade::Graphical_Ncurses::~Graphical_Ncurses()
{
}

void Arcade::Graphical_Ncurses::openWindow()
{
    initscr();
    start_color();
    assume_default_colors(COLOR_WHITE, -1);
    init_pair(1, COLOR_GREEN, -1);
    init_pair(2, COLOR_YELLOW, -1);
    init_pair(3, COLOR_RED, -1);
    init_pair(4, COLOR_WHITE, -1);
    init_pair(5, COLOR_CYAN, -1);
    noecho();
    _window = newwin(product_y(HEIGHT), product_x(WIDTH), 0, 0);
    nodelay(stdscr, true);
    nodelay(_window, true);
    curs_set(0);
    keypad(stdscr, true);
    keypad(_window, true);
}

void Arcade::Graphical_Ncurses::closeWindow()
{
    wclear(_window);
    endwin();
}

void Arcade::Graphical_Ncurses::drawText(graphical_text_t &text)
{
    init_color(10, text.color.r, text.color.g, text.color.b);
    init_pair(10, 10, -1);
    wattron(_window, COLOR_PAIR(10));
    mvwprintw(_window, product_y(text.pos.y), product_x(text.pos.x), text.text.c_str());
    wattroff(_window, COLOR_PAIR(10));
}

void Arcade::Graphical_Ncurses::clear()
{
    werase(_window);
    box(_window, 0, 0);
}

void Arcade::Graphical_Ncurses::refresh()
{
    wrefresh(_window);
}

int Arcade::Graphical_Ncurses::check()
{
    int input = getInput();

    switch (input) {
        case 'a': return 1;
        case 'z': return 2;
        case 'e': return 3;
        case 'r': return 4;
        case 't': return 5;
        case 'y': return 6;
        case 'u': return 7;
        default: return 0;
    }
    return (0);
}

int Arcade::Graphical_Ncurses::getInput()
{
    return (wgetch(stdscr));
}

extern "C" Arcade::IGraphicalModule *entryPoint()
{
    return new Arcade::Graphical_Ncurses;
}