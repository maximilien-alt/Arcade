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
            void setGraphicalModule(IGraphicalModule *newModule) final;
        
        protected:
            IGraphicalModule *_graphicalModule;
            std::list<graphical_text_t> _texts;
    };
}

#endif /* !AGAMEMODULE_HPP_ */
