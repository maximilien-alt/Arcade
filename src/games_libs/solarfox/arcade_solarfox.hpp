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
        private:
            GameClock _mainClock;
            std::unordered_map<size_t, int> _ennemiesDirection;
    };
}

#endif /* !ARCADE_SOLARFOX_HPP_ */
