/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** LibraryManager
*/

#include "LibraryManager.hpp"

Arcade::LibraryManager::LibraryManager(const std::string &name): _startIndex(0)
{
    int index = 0;

    _gameModules.push_back(loadGame("lib/arcade_menu.so"));
    for (const auto & entry : std::filesystem::directory_iterator("lib")) {
        if (entry.path() == "lib/arcade_sfml.so" || entry.path() == "lib/arcade_sdl2.so" || entry.path() == "lib/arcade_ncurses.so") {
            _graphicalModules.push_back(loadLibrary(entry.path()));
            if (entry.path() == name)
                _startIndex = index;
            index += 1;
        } else if (entry.path() != "lib/.gitkeep" && entry.path() != "lib/arcade_menu.so")
            _gameModules.push_back(loadGame(entry.path()));
    }
}

void Arcade::LibraryManager::LibraryManager::reset()
{
    for (auto &n: _graphicalModules)
        n->reset();
    for (auto &n: _gameModules) {
        n->reset();
        n->setPlayerName(_gameModules[0]->getPlayerName());
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

Arcade::IGraphicalModule *Arcade::LibraryManager::getGraphicalModule(size_t index) const
{
    if (index >= _graphicalModules.size())
        return (nullptr);
    return (_graphicalModules[index]);
}

Arcade::IGameModule *Arcade::LibraryManager::getGameModule(size_t index) const
{
    if (index >= _gameModules.size())
        return (nullptr);
    return (_gameModules[index]);
}

size_t Arcade::LibraryManager::getStartIndex() const
{
    return _startIndex;
}

size_t Arcade::LibraryManager::getPreviousGameIndex(size_t index) const
{
    if (index == 1)
        index = _gameModules.size();
    return (index - 1);
}

size_t Arcade::LibraryManager::getNextGameIndex(size_t index) const
{
    index += 1;
    if (index >= _gameModules.size())
        index = 1;
    return (index);
}

size_t Arcade::LibraryManager::getPreviousGraphicalIndex(size_t index) const
{
    if (index == 0)
        index = _graphicalModules.size();
    return (index - 1);
}

size_t Arcade::LibraryManager::getNextGraphicalIndex(size_t index) const
{
    index += 1;
    if (index >= _graphicalModules.size())
        index = 0;
    return (index);
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
