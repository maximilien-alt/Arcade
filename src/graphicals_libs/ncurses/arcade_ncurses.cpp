/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** arcade_ncurses
*/

#include "arcade_ncurses.hpp"

Arcade::Graphical_Ncurses::Graphical_Ncurses() : AGraphicalModule()
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
    curs_set(0);
    _win = newwin(product_y(HEIGHT), product_x(WIDTH), 0, 0);
    keypad(stdscr, true);
    keypad(_win, true);
}

Arcade::Graphical_Ncurses::~Graphical_Ncurses()
{
}

void Arcade::Graphical_Ncurses::drawText(graphical_text_t &text)
{
    init_color(10, text.color.r, text.color.g, text.color.b);
    init_pair(10, 10, -1);
    wattron(_win, COLOR_PAIR(10));
    mvwprintw(_win, product_y(text.pos.y), product_x(text.pos.x), text.text.c_str());
    wattroff(_win, COLOR_PAIR(10));
}

void Arcade::Graphical_Ncurses::clear()
{
    werase(_win);
    box(_win, 0, 0);
}

void Arcade::Graphical_Ncurses::refresh()
{
    wrefresh(_win);
}

int Arcade::Graphical_Ncurses::check()
{
    return (0);
}

extern "C" Arcade::IGraphicalModule *entryPoint()
{
    return new Arcade::Graphical_Ncurses;
}