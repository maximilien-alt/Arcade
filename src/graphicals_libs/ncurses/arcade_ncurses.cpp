/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** arcade_ncurses
*/

#include "arcade_ncurses.hpp"

Arcade::Graphical_Ncurses::Graphical_Ncurses() : AGraphicalModule(), stream("debug.txt", std::ios::app)
{
}

Arcade::Graphical_Ncurses::~Graphical_Ncurses()
{
    stream.close();
}

WINDOW *init_new_window(int a, int b, int c, int d)
{
    WINDOW *win = subwin(stdscr, a, b, c, d);

    nodelay(win, true);
    keypad(win, true);
    return (win);
}

void Arcade::Graphical_Ncurses::openWindow()
{
    initscr();

    start_color();
    assume_default_colors(COLOR_WHITE, -1);
    init_colors_pairs();
    noecho();
    _windows.push_back(init_new_window(product_y(HEIGHT), product_x(WIDTH), 0, 0));
    nodelay(stdscr, true);
    curs_set(0);
    keypad(stdscr, true);
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
    for (auto &n: _windows)
        wclear(n);
    endwin();
}

void Arcade::Graphical_Ncurses::drawSprite(graphical_sprite_t &sprite)
{
    (void)sprite;
}

void Arcade::Graphical_Ncurses::drawText(graphical_text_t &text)
{
    int pair = colornum(text.color.ncurse[0], text.color.ncurse[1]);

    wattron(_windows[0], COLOR_PAIR(pair));
    mvwprintw(_windows[0], product_y(text.pos.y), product_x(text.pos.x), text.text.c_str());
    wattroff(_windows[0], COLOR_PAIR(pair));
}

void Arcade::Graphical_Ncurses::clear()
{
    showBox = false;
    for (auto &n: _windows) {
       werase(n);
       box(n, 0, 0);
    }
}

void Arcade::Graphical_Ncurses::refresh()
{
    wrefresh(_windows[0]);
    if (showBox)
        wrefresh(_windows[1]);
}

void Arcade::Graphical_Ncurses::showInputBox(graphical_box_t &_box)
{
    static int i = 0;

    if (!i++)
        _windows.push_back(init_new_window(product_y(_box.size.y), product_x(_box.size.x), product_y(_box.pos.y), product_x(_box.pos.x)));
    showBox = true;
}

int Arcade::Graphical_Ncurses::check()
{
    int input = getInput();

    for (int index = 1; index < 8; index += 1)
        if (input == KEY_F(index))
            return (index);
    return (0);
}

void Arcade::Graphical_Ncurses::reset()
{

}

int Arcade::Graphical_Ncurses::getInput()
{
    return (wgetch(stdscr));
}

extern "C" Arcade::IGraphicalModule *entryPoint()
{
    return new Arcade::Graphical_Ncurses;
}