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
    // sfText_setCharacterSize(text.text, texte.size);
    // sfText_setString(texte.text, texte.data);
    // // sfText_setFont(texte.text, texte.font);
    // // sfText_setColor (texte.text, texte.color);
    // sfText_setPosition (texte.text, texte.pos);
    // sfRenderWindow_drawText(_window, texte.text, NULL);
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