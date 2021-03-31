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
    if (!_sprites.empty()) {
        for (auto &n: _sprites) {
            if (n.second.second) {
                delwin(n.second.second);
            }
        }
        _sprites.clear();
    }
    for (auto &n: _windows)
        delwin(n);
}

WINDOW *Arcade::Graphical_Ncurses::init_new_window(int a, int b, int c, int d)
{
    WINDOW *win = subwin(stdscr, a, b, c, d);

    if (!win) {
        return nullptr;
    }
    nodelay(win, true);
    keypad(win, true);
    return (win);
}

void Arcade::Graphical_Ncurses::openWindow()
{
    if (_windows.empty()) {
        initscr();

        start_color();
        cbreak();
        mousemask(REPORT_MOUSE_POSITION, NULL);
        assume_default_colors(COLOR_WHITE, -1);
        init_colors_pairs();
        noecho();
        _windows.push_back(init_new_window(product_y(HEIGHT), product_x(WIDTH), 0, 0));
        nodelay(stdscr, true);
        curs_set(0);
        keypad(stdscr, true);
    }
    printf("\033[?1003h\n");
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
            init_pair(colornum(f, b), f, (b == 0) ? -1 : b);
}

void Arcade::Graphical_Ncurses::closeWindow()
{
    for (auto &n: _windows)
        wclear(n);
    printf("\033[?1003l\n");
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

std::vector<std::string> rotate(std::vector<std::string> toRotate, float angle)
{
    // std::vector<std::string> ret;
    // std::string temp;
    // int i = 0;

    // switch ((int)angle) {
    //     case 0: return toRotate;
    //     case 90:
    //         for (int x = 0; x < (int)toRotate[0].length(); x += 1) {
    //             temp.clear();
    //             i = 0;
    //             for (int y = (int)toRotate.size() - 1; y >= 0; y -= 1)
    //                 temp.insert(temp.begin() + i++, 1, toRotate[y][x]);
    //             ret.push_back(temp);
    //         }
    //         break;
    //     case 180:
    //         for (int y = (int)toRotate.size() - 1; y >= 0; y -= 1) {
    //             temp.clear();
    //             i = 0;
    //             for (int x = (int)toRotate[y].length() - 1; x >= 0; x -= 1)
    //                 temp.insert(temp.begin() + i++, 1, toRotate[y][x]);
    //             ret.push_back(temp);
    //         }
    //         break;
    //     case 270:
    //         for (int x = (int)toRotate[0].length() - 1; x >= 0; x -= 1) {
    //             temp.clear();
    //             i = 0;
    //             for (int y = 0; y < (int)toRotate.size(); y += 1)
    //                 temp.insert(temp.begin() + i++, 1, toRotate[y][x]);
    //             ret.push_back(temp);
    //         }
    //         break;
    // }
    // return ret;
    return toRotate;
}

void Arcade::Graphical_Ncurses::drawSprite(graphical_sprite_t &sprite)
{
    int pair = colornum(sprite.color.ncurse[0], sprite.color.ncurse[1]);
    WINDOW *win = nullptr;
    int size_y = 0;
    int size_x = 0;
    int pos_y = product_y(sprite.pos.y);
    int pos_x = product_x(sprite.pos.x);

    if (_sprites.find(sprite.id) == _sprites.end()) {
        std::string temp(sprite.path);
        std::vector<std::string> vector = readFileIntoVector(temp.replace(temp.length() - 3, 3, "txt"));
        size_y = vector.size() + 2;
        size_x = vector[0].length() + 2;
        if (sprite.ncursesBox) {
            win = init_new_window(size_y, size_x, pos_y - size_y / 2, pos_x - size_x / 2);
        }
        _sprites[sprite.id] = std::make_pair(vector, win);
    }
    std::vector<std::string> toPrint = rotate(_sprites[sprite.id].first, sprite.angle);
    size_y = toPrint.size() + 2;
    size_x = toPrint[0].length() + 2;
    sprite.size.y = size_y * HEIGHT / LINES;
    sprite.size.x = size_x * WIDTH / COLS;
    wattron((sprite.ncursesBox) ? _sprites[sprite.id].second : _windows[0], COLOR_PAIR(pair));
    for (size_t index = 0; index < toPrint.size(); index += 1) {
        if (sprite.ncursesBox)
            mvwprintw(_sprites[sprite.id].second, index + 1, 1, toPrint[index].c_str());
        else
            mvwprintw(_windows[0], pos_y - size_y / 2 + index, pos_x - size_x / 2, toPrint[index].c_str());
    }
    wattroff((sprite.ncursesBox) ? _sprites[sprite.id].second : _windows[0], COLOR_PAIR(pair));
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
    if (_windows.size() == 1) {
        int size_y = product_y(_box.size.y) + 1;
        int size_x = product_x(_box.size.x) + 1;
        int pos_y = product_y(_box.pos.y) - 1;
        int pos_x = product_x(_box.pos.x) - 1;

        _windows.push_back(init_new_window(size_y, size_x, pos_y - size_y / 2, pos_x - size_x / 2));
    }
    mvwprintw(_windows[1], 1, 1, _box.input.c_str());
    showBox = true;
}

void Arcade::Graphical_Ncurses::updateInputsMap()
{
    int input = getInput();
    MEVENT event;

    for (int index = 1; index < 8; index += 1)
        if (input == KEY_F(index))
            _keys[index - 1] = 1;
    for (int index = 'a'; index <= 'z'; index += 1)
        if (input == index)
            _keys[index - 'a' + Arcade::KEYS::A] = 1;
    _keys[Arcade::KEYS::RETURN] = (input == '\n');
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
    if (input == 32)
        _keys[Arcade::KEYS::SPACE] = 1;
    _keys[Arcade::KEYS::MOUSE] = getmouse(&event) == OK && input == KEY_MOUSE && (event.bstate & BUTTON1_PRESSED);
}

void Arcade::Graphical_Ncurses::reset()
{
    if (!_sprites.empty()) {
        for (auto &n: _sprites) {
            if (n.second.second) {
                delwin(n.second.second);
            }
        }
        _sprites.clear();
    }
    if (_windows.size() == 2) {
        delwin(_windows[1]);
        _windows.erase(++_windows.begin());
    }
}

bool Arcade::Graphical_Ncurses::isMouseClicked()
{
    int c = getInput();
    return c != ERR && c == KEY_MOUSE;
}

Arcade::graphical_vector_t Arcade::Graphical_Ncurses::getMousePosition()
{
    MEVENT event;
    float x = 0;
    float y = 0;

    if (getmouse(&event) == OK) {
        x = event.x * WIDTH / COLS;
        y = event.y * HEIGHT / LINES;
        stream << y << "|" << x << std::endl;
        return {x, y, 0};
    }
    return {0, 0, 0};
}

int Arcade::Graphical_Ncurses::getInput()
{
    return (wgetch(stdscr));
}

extern "C" Arcade::IGraphicalModule *entryPoint()
{
    return new Arcade::Graphical_Ncurses;
}