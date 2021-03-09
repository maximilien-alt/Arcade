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

            void drawText(graphical_text_t &text);
            void clear();
            void refresh();
        private:
            sf::RenderWindow _window;
            sf::Event _event;
    };
} // namespace Arcade

#endif /* !ARCADE_SFML_HPP_ */