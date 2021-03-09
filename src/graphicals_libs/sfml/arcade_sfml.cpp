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

void Arcade::Graphical_SFML::drawText(graphical_text_t &text)
{
    std::cout << "Jules" << std::endl;
}

extern "C" Arcade::IGraphicalModule *entryPoint()
{
    return new Arcade::Graphical_SFML;
}