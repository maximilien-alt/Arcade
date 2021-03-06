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
#include "GameClock.hpp"

namespace Arcade {
    class AGameModule: public IGameModule {
        public:
            AGameModule();
            virtual ~AGameModule() = default;
            virtual void startGame() = 0;
            virtual int updateGame(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list) = 0;
            void setKeys(std::unordered_map<int, bool> keys) final;
            void setMousePosition(graphical_vector_t pos) final;
            bool isMouseOnSpriteHitbox(graphical_sprite_t sprite) final;
            std::string getPlayerName() const final;
            void setPlayerName(const std::string &name) final;
            void reset() final;

        protected:
            std::vector<graphical_text_t> _texts;
            std::vector<graphical_sprite_t> _sprites;
            std::string _playerName;
            graphical_box_t _box;
            std::unordered_map<int, bool> _keys;
            graphical_vector_t _mousePosition = {0, 0, 0};
    };
}

#endif /* !AGAMEMODULE_HPP_ */
