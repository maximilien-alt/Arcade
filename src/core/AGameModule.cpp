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
    std::cout << "Cc" << std::endl;
    _graphicalModule = newModule;
}