/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** LibraryManager
*/

#include "LibraryManager.hpp"

Arcade::LibraryManager::LibraryManager(const std::string &name)
{
    int check = 0;

    Arcade::IGraphicalModule *graphical = loadLibrary(name);
    _graphicalModules.push_back(graphical);
    _graphicalModules.push_back(loadLibrary("lib/arcade_ncurses.so"));
    Arcade::IGameModule *game = loadGame("./lib/arcade_nibbler.so");
    game->setGraphicalModule(graphical);
    game->startGame();
    while (1) {
        check = game->check();
        switch (check) {
            case 1: game->setGraphicalModule(_graphicalModules[1]);
                break;
            case 2: game->setGraphicalModule(_graphicalModules[1]);
                break;
            case 3: game->setGraphicalModule(_graphicalModules[1]);
                break;
            case 4: game->setGraphicalModule(_graphicalModules[1]);
                break;
            case 5: game->setGraphicalModule(_graphicalModules[1]);
                break;
            case 6: game->setGraphicalModule(_graphicalModules[1]);
                break;
            case 7: game->setGraphicalModule(_graphicalModules[0]);
                break;
            default: break;
        }
        game->updateGame();
    }
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
