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
    _window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Arcade (SFML)");
}

void Arcade::Graphical_SFML::closeWindow()
{
    _window->close();
}

void Arcade::Graphical_SFML::drawSprite(graphical_sprite_t &sprite)
{
    if (_sprites.find(sprite.id) == _sprites.end()) {
        sf::Texture texture;
        if (!texture.loadFromFile(sprite.path))
            return;
        sf::Sprite newsprite(texture);
        newsprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
        _sprites[sprite.id] = {._sprite = newsprite, ._texture = texture};
    }
    sprite.size.y = _sprites[sprite.id]._texture.getSize().y;
    sprite.size.x = _sprites[sprite.id]._texture.getSize().x;
    _sprites[sprite.id]._sprite.setTexture(_sprites[sprite.id]._texture);
    _sprites[sprite.id]._sprite.setPosition(sprite.pos.x, sprite.pos.y);
    _sprites[sprite.id]._sprite.setRotation(sprite.angle);
    _window->draw(_sprites[sprite.id]._sprite);
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
    sf::RectangleShape rectangle(sf::Vector2f(box.size.x, box.size.y));

    rectangle.setPosition(sf::Vector2f(box.pos.x - box.size.x / 2, box.pos.y - box.size.y / 2));
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setOutlineThickness(1);
    rectangle.setOutlineColor(sf::Color::White);
    txt.setString(box.input);
    txt.setCharacterSize(18);
    txt.setFillColor(sf::Color::White);
    txt.setPosition(box.pos.x - box.size.x / 2 + 18, box.pos.y - 18);
    _window->draw(rectangle);
    _window->draw(txt);
}

void Arcade::Graphical_SFML::reset()
{
    // for (auto &texture : _sprites)
    // {
    // }
    _sprites.clear();
    // for (auto &texture : _fonts)
    // {
    // }
    _fonts.clear();
}

Arcade::graphical_vector_t Arcade::Graphical_SFML::getMousePosition()
{
    return {(float)sf::Mouse::getPosition(*_window).x, (float)sf::Mouse::getPosition(*_window).y, 0};
}

bool Arcade::Graphical_SFML::isMouseClicked()
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void Arcade::Graphical_SFML::updateInputsMap()
{
    for (int index = sf::Keyboard::F1; index <= sf::Keyboard::F7; index += 1)
        if (_key[index])
            _keys[index - sf::Keyboard::F1] = 1;
    for (int index = sf::Keyboard::A; index <= sf::Keyboard::Z; index += 1)
        if (_key[index])
            _keys[index - sf::Keyboard::A + Arcade::KEYS::A] = 1;
    if (_key[sf::Keyboard::BackSpace])
        _keys[Arcade::KEYS::BACKSPACE] = 1;
    _keys[Arcade::KEYS::ARROW_LEFT] = _key[sf::Keyboard::Left];
    _keys[Arcade::KEYS::ARROW_RIGHT] = _key[sf::Keyboard::Right];
    _keys[Arcade::KEYS::ARROW_UP] = _key[sf::Keyboard::Up];
    _keys[Arcade::KEYS::ARROW_DOWN] = _key[sf::Keyboard::Down];
    _keys[Arcade::KEYS::RETURN] = _key[sf::Keyboard::Return];
    _keys[Arcade::KEYS::SPACE] = _key[sf::Keyboard::Space];
    _keys[Arcade::KEYS::MOUSE] = sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

extern "C" Arcade::IGraphicalModule *entryPoint()
{
    return new Arcade::Graphical_SFML;
}