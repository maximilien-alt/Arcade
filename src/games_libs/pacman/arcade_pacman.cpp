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

}

Arcade::Game_Pacman::~Game_Pacman()
{

}

void Arcade::Game_Pacman::startGame()
{
    graphical_text_t text;

    if (!_texts.empty()) {
        _texts.clear();
        text.text = std::string("PACMAN");
        text.pos = (graphical_pos_t){WIDTH / 2, HEIGHT / 2, 0};
        text.size = 12;
        _texts.push_back(text);
    }
}

void Arcade::Game_Pacman::updateGame()
{
    _graphicalModule->clear();
    for (auto &n: _texts)
        _graphicalModule->drawText(n);
    _graphicalModule->refresh();
}

__attribute__((constructor))
void constructor()
{
    printf("[libfoo] Loading foo library...\n");
}

__attribute__((destructor))
void destructor()
{
    printf("[libfoo] foo closing...\n");
}

extern "C" Arcade::IGameModule *entryPoint(void)
{
    return new Arcade::Game_Pacman;
}