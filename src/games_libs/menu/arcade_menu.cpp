/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** arcade_menu
*/

#include "arcade_menu.hpp"

Arcade::Game_Menu::Game_Menu(): AGameModule(), _gindex(0)
{
    graphical_text_t text;
    int index = 0;
    float x = 100;
    float y = 100;
    int i = 0;

    for (const auto & entry : std::filesystem::directory_iterator("lib")) {
        if (entry.path() == "lib/arcade_sfml.so" || entry.path() == "lib/arcade_sdl2.so" || entry.path() == "lib/arcade_ncurses.so" || entry.path() == "lib/arcade_menu.so" || entry.path() == "lib/.gitkeep")
            continue;
        std::string path(entry.path());
        index = path.find(".so");
        text.id = i;
        text.text = std::string(path.substr(11, index - 11));
        text.pos = {x, y, 0};
        text.color = {0, 0, 255, {Arcade::COLOR::BLUE, Arcade::COLOR::BLACK}};
        text.size = 12;
        text.font = "ressources/font.ttf";
        _texts.push_back(text);
        y += 100;
        i++;
    }
    _box.pos = {WIDTH / 2, HEIGHT / 2, 0};
    _box.size = {WIDTH / 10, HEIGHT / 10, 0};
    init_sprites();
}

void Arcade::Game_Menu::init_sprites()
{
    graphical_sprite_t sprite;
    int id = 0;

    for (auto &n: _texts) {
        sprite.id = id;
        sprite.path = "ressources/" + n.text + "_logo.png";
        sprite.size = {52, 14, 1};
        sprite.pos = {WIDTH / 2, HEIGHT / 4, 0};
        sprite.ncursesBox = 1;
        sprite.color = {255, 0, 0, {RED, BLACK}};
        id += 1;
        _sprites.push_back(sprite);
    }
}

Arcade::Game_Menu::~Game_Menu()
{

}

void Arcade::Game_Menu::startGame()
{
}

void Arcade::Game_Menu::updatePlayerName()
{
    char ch = 0;

    for (int index = Arcade::KEYS::A; index <= Arcade::KEYS::Z; index += 1) {
        if (_keys[index]) {
            ch = index - Arcade::KEYS::A + 'a';
            _playerName.insert(_playerName.end(), 1, ch);
        }
    }
    if (_keys[Arcade::KEYS::BACKSPACE] && _playerName.length() > 0)
        _playerName.erase(_playerName.length() - 1, 1);
}

void Arcade::Game_Menu::updateGame(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *list)
{
    updatePlayerName();
    if (_keys[Arcade::KEYS::ARROW_LEFT])
        _gindex = _gindex >= 1 ? _gindex - 1 : _sprites.size() - 1;
    if (_keys[Arcade::KEYS::ARROW_RIGHT])
        _gindex = (_gindex + 1) < _sprites.size() ? _gindex + 1 : 0;
    draw(list);
}

void Arcade::Game_Menu::draw(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *list)
{
    size_t index = 0;

    _box.input = _playerName;
    for (auto &n: _sprites) {
        if (index == _gindex) {
            list->push_back(std::make_pair(SPRITE, &n));
            break;
        }
        index += 1;
    }
    list->push_back(std::make_pair(BOX, &_box));
}

extern "C" Arcade::IGameModule *entryPoint(void)
{
    return new Arcade::Game_Menu;
}