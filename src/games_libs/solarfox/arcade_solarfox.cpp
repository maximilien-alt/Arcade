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
    graphical_text_t text;

    text.id = 0;
    text.text = std::string("Solarfox");
    text.pos = {WIDTH / 2, HEIGHT / 2, 0};
    text.color = {255, 0, 0, {Arcade::COLOR::RED, Arcade::COLOR::BLACK}};
    text.size = 12;
    text.font = "ressources/font.ttf";
    _texts.push_back(text);
}

Arcade::Game_Solarfox::~Game_Solarfox()
{

}

void Arcade::Game_Solarfox::startGame()
{
}

int Arcade::Game_Solarfox::updateGame(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list)
{
    for (auto &n : _texts)
        _list->push_back(std::make_pair(TEXT, &n));
    return (0);
}

extern "C" Arcade::IGameModule *entryPoint(void)
{
    return new Arcade::Game_Solarfox;
}