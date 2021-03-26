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
    typedef struct pacman_s
    {
        int position[2];
        graphical_vector_t velocity;
        graphical_vector_t previousVelocity;
        graphical_vector_t buffer;
        int previousPosition[2];
    } pacman_t;

    class Game_Pacman: public AGameModule {
        public:
            Game_Pacman();
            ~Game_Pacman();
        
            void startGame() final;
            int updateGame(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list) final;
            void draw(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list);
            void simulate();
            void initValues();

        private:
            int _currentMapIndex;
            std::vector<std::string> _map;
            pacman_t _pac;
            bool _keyPressed;
            GameClock _mainClock;
            float _start_y;
            float _start_x;

            std::vector<std::string> readFileIntoVector(std::string filepath) const;
    };
}

#endif /* !ARCADE_PACMAN_HPP_ */