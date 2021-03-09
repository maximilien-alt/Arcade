/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** AGameModule
*/

#include "AGameModule.hpp"

Arcade::AGameModule::AGameModule()
{
}

void Arcade::AGameModule::setGraphicalModule(IGraphicalModule *newModule)
{
    if (_graphicalModule)
        _graphicalModule->closeWindow();
    if (newModule) {
        _graphicalModule = newModule;
        _graphicalModule->openWindow();
    }
}

int Arcade::AGameModule::check()
{
    return (_graphicalModule->check());
}