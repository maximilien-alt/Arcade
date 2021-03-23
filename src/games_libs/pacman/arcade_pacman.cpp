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

    text.id = 0;
    text.text = std::string("PACMAN");
    text.pos = {WIDTH / 2, HEIGHT / 2, 0};
    text.color = {255, 0, 0, {Arcade::COLOR::RED, Arcade::COLOR::BLACK}};
    text.size = 12;
    text.font = "ressources/font.ttf";
    _texts.push_back(text);
}

Arcade::Game_Pacman::~Game_Pacman()
{

}

void Arcade::Game_Pacman::startGame()
{
}

void Arcade::Game_Pacman::updateGame(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list)
{
    for (auto &n : _texts)
        _list->push_back(std::make_pair(TEXT, &n));
}

extern "C" Arcade::IGameModule *entryPoint(void)
{
    return new Arcade::Game_Pacman;
}