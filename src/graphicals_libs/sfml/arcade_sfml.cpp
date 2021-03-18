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
    if (_fonts.find(text.font) == _fonts.end()) {
        sf::Font *font = new sf::Font();
        if (!font->loadFromFile(text.font))
            return;
        _fonts[text.font] = font;
    }
    txt.setString(text.text);
    txt.setFont(*(_fonts[text.font]));
    txt.setCharacterSize(text.size);
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

void Arcade::Graphical_SFML::reset()
{

}

void Arcade::Graphical_SFML::updateInptsMap()
{
    for (int index = sf::Keyboard::F1; index <= sf::Keyboard::F7; index += 1)
        if (_key[index])
            _keys[index - sf::Keyboard::F1] = 1;
    for (int index = sf::Keyboard::A; index <= sf::Keyboard::Z; index += 1)
        if (_key[index])
            _keys[index - sf::Keyboard::A + Arcade::KEYS::A] = 1;
    if (_key[sf::Keyboard::BackSpace])
        _keys[Arcade::KEYS::BACKSPACE] = 1;
}

extern "C" Arcade::IGraphicalModule *entryPoint()
{
    return new Arcade::Graphical_SFML;
}