/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** arcade_nibbler
*/

#ifndef ARCADE_NIBBLER_HPP_
#define ARCADE_NIBBLER_HPP_

#include "../../core/AGameModule.hpp"

namespace Arcade {
    class Game_Nibbler: public AGameModule {
        public:
            Game_Nibbler();
            ~Game_Nibbler();
        
            void startGame() final;
            void updateGame() final;
    };
}

#endif /* !ARCADE_NIBBLER_HPP_ */
