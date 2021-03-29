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
            int updateGame(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list) final;
            void draw(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list);
            bool checkDeath();
            void loadMap(int i);
            std::vector<std::string> readFileIntoVector(std::string filepath) const;
            void appleNewPos();

        private:
            std::size_t _indexsnake;
            std::vector<graphical_vector_t> _snake;
            std::vector<graphical_vector_t> _wall;
            graphical_vector_t _apple;
            graphical_vector_t _speed;
            bool _keyPressed = false;
            GameClock _mainClock;
            std::size_t _score;
    };
}

#endif /* !ARCADE_NIBBLER_HPP_ */
