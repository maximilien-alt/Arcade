/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** arcade_SFML
*/

#include "arcade_sfml.hpp"

Arcade::Graphical_SFML::Graphical_SFML() : AGraphicalModule()
{
}

Arcade::Graphical_SFML::~Graphical_SFML()
{
}

void Arcade::Graphical_SFML::openWindow()
{
    _window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "SFML window");
    _window->setFramerateLimit(60);
}

void Arcade::Graphical_SFML::closeWindow()
{
    _window->close();
}

void Arcade::Graphical_SFML::drawSprite(graphical_sprite_t &sprite)
{
    (void)sprite;
}

void Arcade::Graphical_SFML::drawText(graphical_text_t &text)
{
    sf::Font font;
    if (!font.loadFromFile("ressources/font.ttf"))
        return;
    sf::Text txt(text.text, font, text.size);
    txt.setFillColor({text.color.r, text.color.g, text.color.b});
    txt.setPosition(text.pos.x, text.pos.y);
    _window->draw(txt);
}

void Arcade::Graphical_SFML::clear()
{
    for (int i = 0; i < sf::Keyboard::KeyCount; i++)
        _key[i] = false;
    while (_window->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _window->close();
        for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
            _key[i] = _event.type == sf::Event::KeyPressed && \
            _event.key.code == i ? true : _key[i];
        }
    }
    _window->clear(sf::Color::Black);
}

void Arcade::Graphical_SFML::refresh()
{
    _window->display();
}

void Arcade::Graphical_SFML::showInputBox(graphical_box_t &box)
{
    (void)box;
}

int Arcade::Graphical_SFML::check()
{
    if (_key[sf::Keyboard::F1])
        return (1);
    if (_key[sf::Keyboard::F2])
        return (2);
    if (_key[sf::Keyboard::F3])
        return (3);
    if (_key[sf::Keyboard::F4])
        return (4);
    if (_key[sf::Keyboard::F5])
        return (5);
    if (_key[sf::Keyboard::F6])
        return (6);
    if (_key[sf::Keyboard::F7])
        return (7);
    return (0);
}

extern "C" Arcade::IGraphicalModule *entryPoint()
{
    return new Arcade::Graphical_SFML;
}