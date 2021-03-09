/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** IGRAPHICAL_MODULE
*/

#ifndef IGRAPHICAL_MODULE_HPP_
#define IGRAPHICAL_MODULE_HPP_

#define WIDTH 1920
#define HEIGHT 1080

#include "GraphicalStructures.hpp"
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include <vector>
#include <ncurses.h>

namespace Arcade
{
    class IGraphicalModule
    {
    public:
        virtual ~IGraphicalModule() = default;

        virtual void drawText(graphical_text_t &text) = 0;
        virtual void clear() = 0;
        virtual void refresh() = 0;
    };
}

#endif /* !IGRAPHICAL_MODULE_HPP_ */
