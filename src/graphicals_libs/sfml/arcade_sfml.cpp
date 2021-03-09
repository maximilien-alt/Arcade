/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** arcade_SFML
*/

#include "arcade_sfml.hpp"

Arcade::Graphical_SFML::Graphical_SFML() : AGraphicalModule(), _window(sf::VideoMode(WIDTH, HEIGHT), "SFML window")
{
    _window.setFramerateLimit(60);
}

Arcade::Graphical_SFML::~Graphical_SFML()
{
}

void Arcade::Graphical_SFML::drawText(graphical_text_t &text)
{
    sf::Font font;
    if (!font.loadFromFile("src/graphicals_libs/sfml/font.ttf"))
        return;
    sf::Text txt(text.text, font, text.size);
    txt.setColor({text.color.r, text.color.g, text.color.b});
    txt.setPosition(text.pos.x, text.pos.y);
    _window.draw(txt);
}

void Arcade::Graphical_SFML::clear()
{
    _window.clear(sf::Color::Black);
}

void Arcade::Graphical_SFML::refresh()
{
    _window.display();
}

int Arcade::Graphical_SFML::check()
{
    return (0);
}

extern "C" Arcade::IGraphicalModule *entryPoint()
{
    return new Arcade::Graphical_SFML;
}