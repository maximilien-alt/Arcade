/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** arcade_nibbler
*/

#ifndef ARCADE_NIBBLER_HPP_
#define ARCADE_NIBBLER_HPP_

#include "../../core/AGameModule.hpp"

#define TEXTURE_SNAKE_ID 2000
#define TEXTURE_WALL_ID 1000
#define TEXTURE_APPLE_ID 0

namespace Arcade {
    class Game_Nibbler: public AGameModule {
        public:
            Game_Nibbler();
            ~Game_Nibbler();

            void startGame() final;
            void initValues();
            int updateGame(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list) final;
            void draw(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list);
            bool checkDeath();
            bool checkWin();
            bool checkWall(int x, int y);
            void loadMap();
            std::vector<std::string> readFileIntoVector(std::string filepath) const;
            // void appleNewPos();
            // bool inWall(int x, int y);

        private:
            std::size_t _toGrow;
            std::size_t _indexsnake;
            std::vector<graphical_vector_t> _snake;
            std::vector<graphical_vector_t> _wall;
            std::vector<graphical_vector_t> _apple;
            graphical_vector_t _speed;
            graphical_vector_t _speedbuffer;
            bool _keyPressed = false;
            GameClock _mainClock;
            GameClock _timeClock;
            std::size_t _score;
            int _timeleft;
            std::size_t _currentMapIndex = 0;
    };
}

#endif /* !ARCADE_NIBBLER_HPP_ */
