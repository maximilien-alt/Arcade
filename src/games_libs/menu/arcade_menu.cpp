/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** arcade_menu
*/

#include "arcade_menu.hpp"

Arcade::Game_Menu::Game_Menu(): AGameModule()
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
    _box.input = _playerName;
}

Arcade::Game_Menu::~Game_Menu()
{

}

void Arcade::Game_Menu::startGame()
{
}

void Arcade::Game_Menu::updateGame()
{
    _graphicalModule->clear();
    //for (auto &n: _texts)
    //    _graphicalModule->drawText(n);
    //_graphicalModule->showInputBox(_box);
    _graphicalModule->refresh();
}

extern "C" Arcade::IGameModule *entryPoint(void)
{
    return new Arcade::Game_Menu;
}