/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** arcade_ncurses
*/

#include "arcade_ncurses.hpp"

Arcade::Graphical_Ncurses::Graphical_Ncurses() : AGraphicalModule()
{
    _win = newwin(WIDTH, HEIGHT, 0, 0);
    keypad(_win, true);
}

Arcade::Graphical_Ncurses::~Graphical_Ncurses()
{
}

void Arcade::Graphical_Ncurses::drawText(graphical_text_t &text)
{
    mvwprintw(_win, text.pos.y, text.pos.x, text.text.c_str());
}

void Arcade::Graphical_Ncurses::clear()
{
    wclear(_win);
}

void Arcade::Graphical_Ncurses::refresh()
{
    wrefresh(_win);
}

extern "C" Arcade::IGraphicalModule *entryPoint()
{
    return new Arcade::Graphical_Ncurses;
}