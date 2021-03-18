/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** Simulator
*/

#include "Simulator.hpp"

Arcade::Simulator::Simulator(const std::string &path): _libraryManager(path)
{
    _currentGameIndex = 0;
    _currentGraphicalIndex = _libraryManager.getStartIndex();
}

Arcade::Simulator::~Simulator()
{
}

void Arcade::Simulator::run()
{
    Arcade::IGameModule *currentGame = _libraryManager.getGameModule(_currentGameIndex);
    Arcade::IGraphicalModule *currentGraphical = _libraryManager.getGraphicalModule(_currentGraphicalIndex);
    std::unordered_map<int, bool> keys;

    currentGame->setGraphicalModule(currentGraphical, true);
    currentGame->startGame();
    while (1) {
        currentGame->updateGame();
        keys = currentGraphical->getInputsMap();
        if (keys[Arcade::KEYS::F1])
            _currentGraphicalIndex = _libraryManager.getPreviousGraphicalIndex(_currentGraphicalIndex);
        if (keys[Arcade::KEYS::F2])
            _currentGraphicalIndex = _libraryManager.getNextGraphicalIndex(_currentGraphicalIndex);
        if (keys[Arcade::KEYS::F3]) {
            currentGraphical->reset();
            _currentGameIndex = (_currentGameIndex != 0) ? _libraryManager.getPreviousGameIndex(_currentGameIndex) : _currentGameIndex;
        }
        if (keys[Arcade::KEYS::F4]) {
            currentGraphical->reset();
            _currentGameIndex = (_currentGameIndex != 0) ? _libraryManager.getNextGameIndex(_currentGameIndex) : _currentGameIndex;
        }
        if (keys[Arcade::KEYS::F5])
            currentGame->startGame();
        if (keys[Arcade::KEYS::F6])
            _currentGameIndex = 0;
        if (keys[Arcade::KEYS::F7]) {
            currentGraphical->closeWindow();
            break;
        }
        currentGraphical = _libraryManager.getGraphicalModule(_currentGraphicalIndex);
        currentGame = _libraryManager.getGameModule(_currentGameIndex);
        if (keys[Arcade::KEYS::F1] || keys[Arcade::KEYS::F2] || keys[Arcade::KEYS::F3] || keys[Arcade::KEYS::F4])
            currentGame->setGraphicalModule(currentGraphical, (keys[Arcade::KEYS::F1] || keys[Arcade::KEYS::F2]));
    }
}