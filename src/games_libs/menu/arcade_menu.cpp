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

    text.text = std::string("MAIN MENU");
    text.pos = {WIDTH / 2, HEIGHT / 2, 0};
    text.color = {255, 0, 0};
    text.size = 12;
    _texts.push_back(text);
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
    for (auto &n: _texts)
        _graphicalModule->drawText(n);
    _graphicalModule->refresh();
}

extern "C" Arcade::IGameModule *entryPoint(void)
{
    return new Arcade::Game_Menu;
}