/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** AGraphicalModule
*/

#include "AGraphicalModule.hpp"

Arcade::AGraphicalModule::AGraphicalModule()
{
    for (int index = 0; index < NONE; index += 1)
        _keys[index] = 0;
}

void Arcade::AGraphicalModule::resetKeys()
{
    for (auto &n: _keys)
        n.second = 0;
}

std::unordered_map<int, bool> Arcade::AGraphicalModule::getInputsMap() const
{
    return (_keys);
}