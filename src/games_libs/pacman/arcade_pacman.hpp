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
        
            virtual void startGame() final;
            virtual void updateGame() final;
    };
}

#endif /* !ARCADE_PACMAN_HPP_ */

