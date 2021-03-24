/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** arcade_menu
*/

#ifndef ARCADE_MENU_HPP_
#define ARCADE_MENU_HPP_

#include "../../core/AGameModule.hpp"
#include <filesystem>
#include <string>

namespace Arcade
{
    class Game_Menu: public AGameModule {
        public:
            Game_Menu();
            ~Game_Menu();
        
            void startGame() final;
            int updateGame(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list) final;
        
        private:
            size_t _gindex;
            size_t _choiceIndex;
            size_t nbGames;

            void updatePlayerName();
            void init_sprites();
            void draw(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list);
    };
}

#endif /* !ARCADE_MENU_HPP_ */
