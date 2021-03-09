/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** library_manager
*/

#ifndef LIBRARYMANAGER_HPP_
#define LIBRARYMANAGER_HPP_

#include "IGraphicalModule.hpp"

namespace Arcade {
    class LibraryManager
    {
    public:
        LibraryManager(Arcade::IGraphicalModule *graphicalModule);
        ~LibraryManager();
        void openMenu();
        void loadGame();
        void nextGame();
    private:
        Arcade::IGraphicalModule *_graphicalModule;
    };
}

#endif /* !LIBRARYMANAGER_HPP_ */
