/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** Simulator
*/

#ifndef SIMULATOR_HPP_
#define SIMULATOR_HPP_

#include "LibraryManager.hpp"

namespace Arcade {
    class Simulator {
        public:
            Simulator(const std::string &path);
            ~Simulator();

            void run();

        private:
            LibraryManager _libraryManager;

            size_t _currentGraphicalIndex;
            size_t _currentGameIndex;

    };
}

#endif /* !SIMULATOR_HPP_ */
