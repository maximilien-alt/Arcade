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
}

Arcade::Game_Solarfox::~Game_Solarfox()
{

}

void Arcade::Game_Solarfox::startGame()
{
    _box.pos = {WIDTH / 2, HEIGHT / 2, 0};
    _box.size = {40 * 15, 40 * 15, 0};

    graphical_sprite_t sprite;
    sprite.id = 0;
    sprite.path = "ressources/solarfox_ennemy_up.png";
    sprite.color = {255, 0, 0, {RED, RED}};
    sprite.pos = {(_box.pos.x - _box.size.x / 2 + 120), (_box.pos.y - _box.size.y / 2 + 8), 0};
    sprite.size = {36, 18, 0};
    _sprites.push_back(sprite);

    _ennemiesDirection[0] = 1;
    _ennemiesDirection[1] = 1;
    _ennemiesDirection[2] = -1;
    _ennemiesDirection[3] = -1;
}

int Arcade::Game_Solarfox::updateGame(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *list)
{
    if (_mainClock.getElapsedTime() > 0.005) {
        _mainClock.reset();
        _sprites[0].pos.x += _ennemiesDirection[0];
        if (_sprites[0].pos.x >= _box.pos.x - _box.size.x / 2 + _box.size.x - 16) {
            _ennemiesDirection[0] = -1;
        } else if (_sprites[0].pos.x <= _box.pos.x - _box.size.x / 2 + 16)
            _ennemiesDirection[0] = 1;
    }

    draw(list);
    return (0);
}

void Arcade::Game_Solarfox::draw(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *list)
{
    list->push_back(std::make_pair(BOX, &_box));
    for (auto &n : _texts)
        list->push_back(std::make_pair(TEXT, &n));
    for (auto &n : _sprites)
        list->push_back(std::make_pair(SPRITE, &n));
}

extern "C" Arcade::IGameModule *entryPoint(void)
{
    return new Arcade::Game_Solarfox;
}