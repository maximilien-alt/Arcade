/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** Simulator
*/

#include "Simulator.hpp"

Arcade::Simulator::Simulator(const std::string &path): _libraryManager(path)
{
    _currentGameIndex = 1;
    _currentGraphicalIndex = _libraryManager.getStartIndex();
}

Arcade::Simulator::~Simulator()
{
}

void Arcade::Simulator::run()
{
    Arcade::IGameModule *currentGame = _libraryManager.getGameModule(_currentGameIndex);
    Arcade::IGraphicalModule *currentGraphical = _libraryManager.getGraphicalModule(_currentGraphicalIndex);
    int check = 0;

    currentGame->setGraphicalModule(currentGraphical, true);
    currentGame->startGame();
    while (1) {
        check = currentGame->check();
        switch (check) {
            case 1: _currentGraphicalIndex = _libraryManager.getPreviousGraphicalIndex(_currentGraphicalIndex);
                break;
            case 2: _currentGraphicalIndex = _libraryManager.getNextGraphicalIndex(_currentGraphicalIndex);
                break;
            case 3: _currentGameIndex = (_currentGameIndex != 0) ? _libraryManager.getPreviousGameIndex(_currentGameIndex) : _currentGameIndex;
                break;
            case 4: _currentGameIndex = (_currentGameIndex != 0) ? _libraryManager.getNextGameIndex(_currentGameIndex) : _currentGameIndex;
                break;
            case 5: currentGame->startGame();
                break;
            case 6: _currentGameIndex = 0;
                break;
            case 7: currentGraphical->closeWindow();
                return;
            default: break;
        }
        currentGraphical = _libraryManager.getGraphicalModule(_currentGraphicalIndex);
        currentGame = _libraryManager.getGameModule(_currentGameIndex);
        if (check > 0 && check < 5)
            currentGame->setGraphicalModule(currentGraphical, (check == 1 || check == 2));
        currentGame->updateGame();
    }
}