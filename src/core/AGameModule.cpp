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

void Arcade::AGameModule::setGraphicalModule(IGraphicalModule *newModule, bool update)
{
    if (_graphicalModule && update)
        _graphicalModule->closeWindow();
    if (newModule) {
        _graphicalModule = newModule;
        if (update)
            _graphicalModule->openWindow();
    }
}

Arcade::IGraphicalModule *Arcade::AGameModule::getGraphicalModule() const
{
    return (_graphicalModule);
}

Arcade::IGameModule *Arcade::AGameModule::operator=(const IGameModule *copy)
{
    _graphicalModule = copy->getGraphicalModule();
    return (this);
}

int Arcade::AGameModule::check()
{
    return (_graphicalModule->check());
}