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

    currentGraphical->openWindow();
    currentGame->startGame();
    while (1) {
        currentGame->updateGame(&_list);
        keys = currentGraphical->getInputsMap();
        if (keys[Arcade::KEYS::F1]) {
            currentGraphical->closeWindow();
            _currentGraphicalIndex = _libraryManager.getPreviousGraphicalIndex(_currentGraphicalIndex);
        }
        if (keys[Arcade::KEYS::F2]) {
            currentGraphical->closeWindow();
            _currentGraphicalIndex = _libraryManager.getNextGraphicalIndex(_currentGraphicalIndex);
        }
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
        if (keys[Arcade::KEYS::F1] || keys[Arcade::KEYS::F2])
            currentGraphical->openWindow();
        parseList(currentGraphical, currentGame);
        if (!_list.empty())
            _list.clear();
    }
}

void Arcade::Simulator::parseList(Arcade::IGraphicalModule *currentGraphical, Arcade::IGameModule *currentGame)
{
    currentGraphical->resetKeys();
    currentGraphical->clear();
    currentGraphical->updateInputsMap();
    currentGame->setKeys(currentGraphical->getInputsMap());
    for (auto &n: _list) {
        switch (n.first) {
            case SPRITE:
                currentGraphical->drawSprite(*dynamic_cast<Arcade::graphical_sprite_t *>(n.second));
                break;
            case TEXT:
                currentGraphical->drawText(*dynamic_cast<Arcade::graphical_text_t *>(n.second));
                break;
            case BOX:
                currentGraphical->showInputBox(*dynamic_cast<Arcade::graphical_box_t *>(n.second));
                break;
            default:
                break;
        }
    }
    currentGraphical->refresh();
}