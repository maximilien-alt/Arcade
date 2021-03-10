/*
** EPITECH PROJECT, 2021
** bootstrap_arcade
** File description:
** lib1
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "arcade_nibbler.hpp"

Arcade::Game_Nibbler::Game_Nibbler(): AGameModule()
{
    graphical_text_t text;

    if (!_texts.empty())
        _texts.clear();
    text.text = std::string("NIBBLER");
    text.pos = {WIDTH / 2, HEIGHT / 2, 0};
    text.color = {255, 0, 0};
    text.size = 12;
    _texts.push_back(text);
}

Arcade::Game_Nibbler::~Game_Nibbler()
{

}

void Arcade::Game_Nibbler::startGame()
{
}

void Arcade::Game_Nibbler::updateGame()
{
    _graphicalModule->clear();
    for (auto &n: _texts)
        _graphicalModule->drawText(n);
    _graphicalModule->refresh();
}

extern "C" Arcade::IGameModule *entryPoint(void)
{
    return new Arcade::Game_Nibbler;
}