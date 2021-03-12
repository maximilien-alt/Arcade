/*
** EPITECH PROJECT, 2021
** bootstrap_arcade
** File description:
** lib1
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "arcade_pacman.hpp"

Arcade::Game_Pacman::Game_Pacman(): AGameModule()
{
    graphical_text_t text;

    text.text = std::string("PACMAN");
    text.pos = {WIDTH / 2, HEIGHT / 2, 0};
    text.color = {255, 0, 0, {Arcade::COLOR::RED, Arcade::COLOR::BLACK}};
    text.size = 12;
    _texts.push_back(text);
}

Arcade::Game_Pacman::~Game_Pacman()
{

}

void Arcade::Game_Pacman::startGame()
{
}

void Arcade::Game_Pacman::updateGame()
{
    _graphicalModule->clear();
    for (auto &n : _texts)
        _graphicalModule->drawText(n);
    _graphicalModule->refresh();
}

extern "C" Arcade::IGameModule *entryPoint(void)
{
    return new Arcade::Game_Pacman;
}