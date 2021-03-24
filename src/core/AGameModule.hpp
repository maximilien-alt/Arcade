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
            virtual void startGame() = 0;
            virtual int updateGame(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list) = 0;
            void setKeys(std::unordered_map<int, bool> keys) final;
            void setMouseClickedStatus(bool status) final;
            void setMousePosition(graphical_vector_t pos) final;
            bool isMouseClickedOnSprite(graphical_sprite_t sprite) final;

        protected:
            std::list<graphical_text_t> _texts;
            std::vector<graphical_sprite_t> _sprites;
            std::string _playerName;
            graphical_box_t _box;
            std::unordered_map<int, bool> _keys;
            bool _mouseClicked;
            graphical_vector_t _mousePosition;
    };
}

#endif /* !AGAMEMODULE_HPP_ */
