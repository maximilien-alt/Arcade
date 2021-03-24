/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** arcade_solarfox
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "arcade_solarfox.hpp"

Arcade::Game_Solarfox::Game_Solarfox(): AGameModule()
{
    _box.pos = {WIDTH / 2, HEIGHT / 2, 0};
    _box.size = {40 * 15, 40 * 15, 0};
}

Arcade::Game_Solarfox::~Game_Solarfox()
{

}

void Arcade::Game_Solarfox::startGame()
{
}

int Arcade::Game_Solarfox::updateGame(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *list)
{
    for (auto &n : _texts)
        list->push_back(std::make_pair(TEXT, &n));
    list->push_back(std::make_pair(BOX, &_box));
    return (0);
}

extern "C" Arcade::IGameModule *entryPoint(void)
{
    return new Arcade::Game_Solarfox;
}