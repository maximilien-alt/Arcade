/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** library_manager
*/

#ifndef LIBRARYMANAGER_HPP_
#define LIBRARYMANAGER_HPP_

#include "IGameModule.hpp"
#include <vector>
#include <filesystem>
#include <iostream>
#include <string>
#include "LDL.hpp"
#include "Errors.hpp"

namespace Arcade {
    class LibraryManager
    {
    public:
        LibraryManager(const std::string &name);
        ~LibraryManager();
        void openMenu();
        void loadGame();
        void nextGame();

        Arcade::IGraphicalModule *getGraphicalModule(size_t index) const;
        Arcade::IGameModule *getGameModule(size_t index) const;
        size_t getStartIndex() const;
        size_t getPreviousGameIndex(size_t index) const;
        size_t getNextGameIndex(size_t index) const;
        size_t getPreviousGraphicalIndex(size_t index) const;
        size_t getNextGraphicalIndex(size_t index) const;

    private:
        std::vector<Arcade::IGraphicalModule *> _graphicalModules;
        std::vector<Arcade::IGameModule *> _gameModules;

        size_t _startIndex;

        Arcade::IGraphicalModule *loadLibrary(const std::string &name);
        Arcade::IGameModule *loadGame(const std::string &name);

    };
}

#endif /* !LIBRARYMANAGER_HPP_ */
