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
            virtual void updateGame(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list) = 0;
            virtual void setKeys(std::unordered_map<int, bool> keys) = 0;
    };
}

#endif /* !IGAMEMODULE_HPP_ */
