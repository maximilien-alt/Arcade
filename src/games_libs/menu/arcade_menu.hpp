/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** arcade_menu
*/

#ifndef ARCADE_MENU_HPP_
#define ARCADE_MENU_HPP_

#include "../../core/AGameModule.hpp"

namespace Arcade
{
    class Game_Menu: public AGameModule {
        public:
            Game_Menu();
            ~Game_Menu();
        
            void startGame() final;
            void updateGame() final;
    };
}

#endif /* !ARCADE_MENU_HPP_ */
