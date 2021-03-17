/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** arcade_SFML
*/

#ifndef ARCADE_SFML_HPP_
#define ARCADE_SFML_HPP_

#include "../../core/AGraphicalModule.hpp"

namespace Arcade
{
    class Graphical_SFML : public AGraphicalModule {
        public:
            Graphical_SFML();
            ~Graphical_SFML();

            void drawSprite(graphical_sprite_t &sprite) final;
            void drawText(graphical_text_t &text) final;
            void showInputBox(graphical_box_t &box) final;
            void reset() final;
            void clear() final;
            void refresh() final;
            int check() final;
            void openWindow() final;
            void closeWindow() final;

        private:
            sf::RenderWindow *_window;
            sf::Event _event;
            sf::Text txt;
            std::unordered_map<std::string, sf::Font *> _fonts;
            bool _key[sf::Keyboard::KeyCount];
    };
} // namespace Arcade

#endif /* !ARCADE_SFML_HPP_ */
