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
    typedef struct sfml_sprite_s {
        sf::Sprite _sprite;
        sf::Texture _texture;
    } sfml_sprite_t;

    class Graphical_SFML : public AGraphicalModule {
        public:
            Graphical_SFML();
            ~Graphical_SFML();

            void drawSprite(graphical_sprite_t &sprite) final;
            void drawText(graphical_text_t &text) final;
            void showInputBox(graphical_box_t &box) final;
            bool isMouseClicked() final;
            graphical_vector_t getMousePosition() final;
            void reset() final;
            void clear() final;
            void refresh() final;
            void updateInputsMap() final;
            void openWindow() final;
            void closeWindow() final;

        private:
            sf::RenderWindow *_window;
            sf::Event _event;
            sf::Text txt;
            std::unordered_map<std::string, sf::Font *> _fonts;
            std::unordered_map<int, sfml_sprite_t> _sprites;
            bool _key[sf::Keyboard::KeyCount];
    };
} // namespace Arcade

#endif /* !ARCADE_SFML_HPP_ */
