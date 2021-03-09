/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** arcade_SFML
*/

#include "arcade_sfml.hpp"

Arcade::Graphical_SFML::Graphical_SFML() : AGraphicalModule()
{
    _window = sfRenderWindow_create({1920, 1080, 32}, "TEST", sfFullscreen, NULL);
    sfRenderWindow_setFramerateLimit(_window, 60);
}

Arcade::Graphical_SFML::~Graphical_SFML()
{
}

void Arcade::Graphical_SFML::drawText(graphical_text_t &text)
{
    std::cout << "Jules" << std::endl;
    // sfText_setCharacterSize(text.text, texte.size);
    // sfText_setString(texte.text, texte.data);
    // sfText_setFont(texte.text, texte.font);
    // sfText_setColor (texte.text, texte.color);
    // sfText_setPosition (texte.text, texte.pos);
    // sfRenderWindow_drawText(_window, texte.text, NULL);
}

void Arcade::Graphical_SFML::poll_event()
{
    while (sfRenderWindow_pollEvent(_window, &_event)) {
    }
}

extern "C" Arcade::IGraphicalModule *entryPoint()
{
    return new Arcade::Graphical_SFML;
}

// void update(sfRenderWindow *window, sfEvent event)
// {
//     sfRenderWindow_clear(window, sfBlack);
//     poll_event(window, event);
//     sfRenderWindow_display(window);
// }