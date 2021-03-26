/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** ARCADE_PACMAN
*/

#ifndef ARCADE_PACMAN_HPP_
#define ARCADE_PACMAN_HPP_

#include "../../core/AGameModule.hpp"

namespace Arcade {
    class Game_Pacman: public AGameModule {
        public:
            Game_Pacman();
            ~Game_Pacman();
        
            void startGame() final;
            int updateGame(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list) final;

        private:
            int _currentMapIndex;
            std::vector<std::string> _map;

            std::vector<std::string> readFileIntoVector(std::string filepath) const;
    };
}

#endif /* !ARCADE_PACMAN_HPP_ */