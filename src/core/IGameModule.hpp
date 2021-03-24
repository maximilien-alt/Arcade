/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** IGameModule
*/

#ifndef IGAMEMODULE_HPP_
#define IGAMEMODULE_HPP_

#include "IGraphicalModule.hpp"

namespace Arcade {
    class IGameModule {
        public:
            virtual ~IGameModule() = default;

            virtual void startGame() = 0;
            virtual int updateGame(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list) = 0;
            virtual void setKeys(std::unordered_map<int, bool> keys) = 0;
            virtual void setMouseClickedStatus(bool status) = 0;
            virtual void setMousePosition(graphical_vector_t pos) = 0;
            virtual bool isMouseOnSpriteHitbox(graphical_sprite_t sprite) = 0;
            virtual void runClock() = 0;
    };
}

#endif /* !IGAMEMODULE_HPP_ */
