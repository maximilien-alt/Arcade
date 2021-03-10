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
    int IGame = 0;
    int IGraphical = 0;

    for (const auto & entry : std::filesystem::directory_iterator("lib")) {
        if (entry.path() == "lib/arcade_sfml.so" || entry.path() == "lib/arcade_sdl2.so" || entry.path() == "lib/arcade_ncurses.so") {
            _graphicalModules.push_back(loadLibrary(entry.path()));
            if (entry.path() == name)
                _currentGraphical = IGraphical;
            IGraphical++;
        } else if (entry.path() != "lib/.gitkeep") {
            _gameModules.push_back(loadGame(entry.path()));
            if (entry.path() == "lib/arcade_pacman.so")
                _currentGame = IGame;
            IGame++;
        }
    }
    _gameModules[_currentGame]->setGraphicalModule(_graphicalModules[_currentGraphical]);
    _gameModules[_currentGame]->startGame();
    while (1) {
        check = _gameModules[_currentGame]->check();
        switch (check) {
            case 1: _gameModules[_currentGame]->setGraphicalModule(_graphicalModules[1]);
                break;
            case 2: _gameModules[_currentGame]->setGraphicalModule(_graphicalModules[2]);
                break;
            case 3: _gameModules[_currentGame]->setGraphicalModule(_graphicalModules[1]);
                break;
            case 4: _gameModules[_currentGame]->setGraphicalModule(_graphicalModules[1]);
                break;
            case 5: _gameModules[_currentGame]->setGraphicalModule(_graphicalModules[1]);
                break;
            case 6: _gameModules[_currentGame]->setGraphicalModule(_graphicalModules[1]);
                break;
            case 7: _gameModules[_currentGame]->setGraphicalModule(_graphicalModules[0]);
                break;
            default: break;
        }
        _gameModules[_currentGame]->updateGame();
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
