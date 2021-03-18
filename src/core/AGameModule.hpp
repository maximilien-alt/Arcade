/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** AGameModule
*/

#ifndef AGAMEMODULE_HPP_
#define AGAMEMODULE_HPP_

#include "IGameModule.hpp"
#include "GraphicalStructures.hpp"

namespace Arcade {
    class AGameModule: public IGameModule {
        public:
            AGameModule();
            virtual ~AGameModule() = default;
            void setGraphicalModule(IGraphicalModule *newModule, bool) final;
            virtual void startGame() = 0;
            virtual void updateGame() = 0;
            IGameModule *operator=(const IGameModule *copy) final;
            IGraphicalModule *getGraphicalModule() const;

        protected:
            IGraphicalModule *_graphicalModule = nullptr;
            std::list<graphical_text_t> _texts;
            std::string _playerName;
            graphical_box_t _box;
            std::unordered_map<int, bool> _keys;
    };
}

#endif /* !AGAMEMODULE_HPP_ */
