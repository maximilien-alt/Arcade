/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** ARCADE_PACMAN
*/

#ifndef ARCADE_PACMAN_HPP_
#define ARCADE_PACMAN_HPP_

#include "../../core/AGameModule.hpp"
#include <unordered_map>

namespace Arcade {
    typedef struct pacman_s
    {
        int position[2];
        graphical_vector_t velocity;
        graphical_vector_t previousVelocity;
        graphical_vector_t buffer;
        int spwanPosition[2];
        int previousPosition[2];
        GameClock draw;
    } pacman_t;

    typedef struct ghost_s
    {
        int position[2];
        int previousPosition[2];
        graphical_vector_t velocity;
        bool isfree;
        bool isFreeze;
        GameClock clock;
        GameClock eaten;
        int spwanPosition[2];
        std::vector<graphical_sprite_t> sprites;
        int jail[2];
        int fIterations;
        bool isDead;
        std::vector<std::string> path;
        GameClock draw;
    } ghost_t;

    class Game_Pacman: public AGameModule {
        public:
            Game_Pacman();
            ~Game_Pacman();
        
            void startGame() final;
            int updateGame(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list) final;
            void draw(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list);
            bool simulate();
            void initValues();

        private:
            int _currentMapIndex;
            std::vector<std::string> _map;
            int _score;
            pacman_t _pac;
            std::vector<ghost_t> _ghosts;
            bool _keyPressed;
            GameClock _mainClock;
            float _start_y;
            float _start_x;
            float _level;
            int _pacgums;
            int _pacgumsTotal;
            int _beginId;
            int _life;
            int _lifeMax;
            AStar star;

            std::vector<std::string> readFileIntoVector(std::string filepath) const;
            void getPacVelocity();
            void updateGhosts();
            void ghostMovement(ghost_t &ghost);
            void loadMap();
            void updatePacGums();
            void followPath(ghost_t &ghost);
            void smoothDraw(int prev[2], int now[2], graphical_sprite_t &sprite, GameClock clock);
    };
}

#endif /* !ARCADE_PACMAN_HPP_ */