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
    init_colors_pairs();
    noecho();
    _window = newwin(product_y(HEIGHT), product_x(WIDTH), 0, 0);
    nodelay(stdscr, true);
    nodelay(_window, true);
    curs_set(0);
    keypad(stdscr, true);
    keypad(_window, true);
}

int colornum(int f, int bg)
{
    int a = 1 << 7;
    int b = (7 & bg) << 4;
    int c = 7 & f;

    return (a | b | c);
}

void Arcade::Graphical_Ncurses::init_colors_pairs()
{
    for (int f = 0; f <= 7; f += 1)
        for (int b = 0; b <= 7; b += 1)
            init_pair(colornum(f, b), f, b);
}

void Arcade::Graphical_Ncurses::closeWindow()
{
    wclear(_window);
    endwin();
}

void Arcade::Graphical_Ncurses::drawSprite(graphical_sprite_t &sprite)
{
    (void)sprite;
}

void Arcade::Graphical_Ncurses::drawText(graphical_text_t &text)
{
    int pair = colornum(text.color.ncurse[0], text.color.ncurse[1]);

    wattron(_window, COLOR_PAIR(pair));
    mvwprintw(_window, product_y(text.pos.y), product_x(text.pos.x), text.text.c_str());
    wattroff(_window, COLOR_PAIR(pair));
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