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
    private:
        std::vector<Arcade::IGraphicalModule *> _graphicalModules;
        std::vector<Arcade::IGameModule *> _gameModules;

        int _currentGame;
        int _currentGraphical;

        Arcade::IGraphicalModule *loadLibrary(const std::string &name);
        Arcade::IGameModule *loadGame(const std::string &name);
    };
}

#endif /* !LIBRARYMANAGER_HPP_ */
