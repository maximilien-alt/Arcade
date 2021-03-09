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
            virtual void updateGame() = 0;
            virtual void setGraphicalModule(IGraphicalModule *newModule) = 0;
    };
}

#endif /* !IGAMEMODULE_HPP_ */
