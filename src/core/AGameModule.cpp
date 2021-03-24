/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** AGameModule
*/

#include "AGameModule.hpp"

Arcade::AGameModule::AGameModule()
{
    _box.pos = {0, 0, 0};
    _box.size = {0, 0, 0};
}

void Arcade::AGameModule::setKeys(std::unordered_map<int, bool> keys)
{
    _keys = keys;
}

void Arcade::AGameModule::runClock()
{
    _tick = false;
    _clock++;
    if (_clock >= _fps) {
        _tick = true;
        _clock = 0;
    }
}