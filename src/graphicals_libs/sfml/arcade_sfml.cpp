/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** arcade_SFML
*/

#include "arcade_sfml.hpp"

Arcade::Graphical_SFML::Graphical_SFML() : AGraphicalModule(), _window(sf::VideoMode(800, 600), "SFML window")
{
    _window.setFramerateLimit(60);
}

Arcade::Graphical_SFML::~Graphical_SFML()
{
}

void Arcade::Graphical_SFML::drawText(graphical_text_t &text)
{
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        return;
    sf::Text txt("Hello SFML", font, 50);
    txt.setColor(sf::Color::Green);
    txt.setPosition(text.pos.x, text.pos.y);
    _window.draw(txt);
}

extern "C" Arcade::IGraphicalModule *entryPoint()
{
    return new Arcade::Graphical_SFML;
}

// void update(sfRenderWindow *window, sfEvent event)
// {
//     sfRenderWindow_clear(window, sfBlack);
//     sfRenderWindow_display(window);
// }