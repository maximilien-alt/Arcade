/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** arcade_solarfox
*/

#ifndef ARCADE_SOLARFOX_HPP_
#define ARCADE_SOLARFOX_HPP_

#include "../../core/AGameModule.hpp"

namespace Arcade {
    class Game_Solarfox: public AGameModule {
        public:
            Game_Solarfox();
            ~Game_Solarfox();

            void startGame() final;
            int updateGame(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list) final;
            void draw(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *list);
            void createEnnemies();
            void createPlayer();
            void createPowerUps();
            void calcEnnemiesPositions();
            void calcPlayerPosition();
            void calcEnnemiesShots();
            void calcPowerUpsShots();
            void endGame();
            void handleKeys();
            int distanceBetween(graphical_vector_t pos1, graphical_vector_t pos2);
            void ennemyShot(graphical_sprite_t &sprite, GameClock &clock);
            std::vector<std::string> readFileIntoVector(std::string filepath) const;
            void playerShot();
        private:
            size_t _spriteIndex = 0;
            GameClock _mainClock;
            GameClock _ennemiesShotClocks;
            GameClock _shotClock;
            std::vector<GameClock> _ennemiesClocks;
            std::vector<std::pair<graphical_sprite_t, float>> _ennemiesShots;
            std::vector<std::pair<graphical_sprite_t, size_t>> _powerUps;
            std::unordered_map<size_t, float> _ennemiesDirection;
            size_t _currentMapIndex = 1;
            size_t _playerDirection = 0;
    };
}

#endif /* !ARCADE_SOLARFOX_HPP_ */
