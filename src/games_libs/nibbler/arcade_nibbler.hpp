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

        enum NIBBLER {
            VOID,
            SNAKE,
            APPLE
        };

        public:
            Game_Nibbler();
            ~Game_Nibbler();

            void startGame() final;
            int updateGame(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list) final;
            void draw(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list);
            bool checkDeath();

        private:
            std::size_t _indexsprite = 0;
            std::vector<graphical_vector_t> _snake;
            graphical_vector_t _apple;
            graphical_vector_t _speed;
            bool _keyPressed = false;
            GameClock _mainClock;
    };
}

#endif /* !ARCADE_NIBBLER_HPP_ */
