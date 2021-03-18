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

std::vector<std::string> Arcade::Graphical_Ncurses::readFileIntoVector(std::string filepath)
{
    std::vector<std::string> res;
    std::ifstream file(filepath);
    std::string temp;

    if (file.is_open()) {
        while (std::getline(file, temp)) {
            res.push_back(temp);
        }
    }
    return (res);
}

void Arcade::Graphical_Ncurses::drawSprite(graphical_sprite_t &sprite)
{
    int pair = colornum(sprite.color.ncurse[0], sprite.color.ncurse[1]);
    WINDOW *win = nullptr;

    if (_sprites.find(sprite.id) == _sprites.end()) {
        std::vector<std::string> vector = readFileIntoVector(sprite.ncurses_path);
        if (sprite.ncursesBox) {
            win = init_new_window(sprite.size.y, sprite.size.y, sprite.pos.y, sprite.pos.x);
        }
        _sprites[sprite.id] = std::make_pair(vector, win);
    }
    win = (sprite.ncursesBox) ? _sprites[sprite.id].second : _windows[0];
    wattron(win, COLOR_PAIR(pair));
    for (size_t index = 0; index < _sprites[sprite.id].first.size(); index += 1) {
        mvwprintw(win, product_y(sprite.pos.y) + index, product_x(sprite.pos.x), _sprites[sprite.id].first[index].c_str());
    }
    wattroff(win, COLOR_PAIR(pair));
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
    for (auto &n: _sprites) {
        if (n.second.second != nullptr) {
            werase(n.second.second);
            box(n.second.second, 0, 0);
        }
    }
}

void Arcade::Graphical_Ncurses::refresh()
{
    wrefresh(_windows[0]);
    if (showBox)
        wrefresh(_windows[1]);
    for (auto &n: _sprites) {
        if (n.second.second != nullptr) {
            wrefresh(n.second.second);
        }
    }
}

void Arcade::Graphical_Ncurses::showInputBox(graphical_box_t &_box)
{
    static int i = 0;

    if (!i) {
        int size_y = product_y(_box.size.y);
        int size_x = product_x(_box.size.x);
        int pos_y = product_y(_box.pos.y);
        int pos_x = product_x(_box.pos.x);

        _windows.push_back(init_new_window(size_y, size_x, pos_y - size_y / 2, pos_x - size_x / 2));
        i = 1;
    }
    mvwprintw(_windows[1], 1, 1, _box.input.c_str());
    showBox = true;
}

void Arcade::Graphical_Ncurses::updateInputsMap()
{
    int input = getInput();

    for (int index = 1; index < 8; index += 1)
        if (input == KEY_F(index))
            _keys[index - 1] = 1;
    for (int index = 'a'; index <= 'z'; index += 1)
        if (input == index)
            _keys[index - 'a' + Arcade::KEYS::A] = 1;
    if (input == KEY_RIGHT)
        _keys[Arcade::KEYS::ARROW_RIGHT] = 1;
    if (input == KEY_LEFT)
        _keys[Arcade::KEYS::ARROW_LEFT] = 1;
    if (input == KEY_UP)
        _keys[Arcade::KEYS::ARROW_UP] = 1;
    if (input == KEY_DOWN)
        _keys[Arcade::KEYS::ARROW_DOWN] = 1;
    if (input == KEY_BACKSPACE || input == KEY_DC)
        _keys[Arcade::KEYS::BACKSPACE] = 1;
}

void Arcade::Graphical_Ncurses::reset()
{
    _sprites.clear();
}

int Arcade::Graphical_Ncurses::getInput()
{
    return (wgetch(stdscr));
}

extern "C" Arcade::IGraphicalModule *entryPoint()
{
    return new Arcade::Graphical_Ncurses;
}