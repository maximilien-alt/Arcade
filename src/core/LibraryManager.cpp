/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** LibraryManager
*/

#include "LibraryManager.hpp"

Arcade::LibraryManager::LibraryManager(const std::string &name)
{
    _graphicalModules.push_back(std::move(loadLibrary(name)));
}

Arcade::LibraryManager::~LibraryManager()
{
    // for (auto graphicalModules : _graphicalModules)
    //     delete graphicalModules;
}

Arcade::IGraphicalModule *Arcade::LibraryManager::loadLibrary(const std::string &name)
{
    void *handle = LDL::open(name.c_str());
    Arcade::IGraphicalModule *(*entryPoint)(void) = NULL;

    if (!handle)
        throw Errors("Unable to load library " + name + " : " + LDL::error());

    *(void **)(&entryPoint) = LDL::sym(handle, "entryPoint");
    if (entryPoint == NULL)
        throw Errors("Unable to load library " + name + " : Invalid library");

    Arcade::IGraphicalModule *graphicalModule = entryPoint();
    LDL::close(handle);
    return (graphicalModule);
}

Arcade::IGameModule *Arcade::LibraryManager::loadGame(const std::string &name)
{
    void *handle = LDL::open(name.c_str());
    Arcade::IGameModule *(*entryPoint)(void) = NULL;

    if (!handle)
        throw Errors("Unable to load library " + name + " : " + LDL::error());

    *(void **)(&entryPoint) = LDL::sym(handle, "entryPoint");
    if (entryPoint == NULL)
        throw Errors("Unable to load library " + name + " : Invalid library");

    Arcade::IGameModule *gameModule = entryPoint();
    LDL::close(handle);
    return (gameModule);
}

void Arcade::LibraryManager::openMenu()
{
    // _graphicalModule->init();
    // _graphicalModule->open();
}

void Arcade::LibraryManager::loadGame()
{
    // _graphicalModule->init();
    // _graphicalModule->open();
}

void Arcade::LibraryManager::nextGame()
{
    // load other Game
}
