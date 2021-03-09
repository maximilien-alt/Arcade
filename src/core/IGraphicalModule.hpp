/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** IGRAPHICAL_MODULE
*/

#ifndef IGRAPHICAL_MODULE_HPP_
#define IGRAPHICAL_MODULE_HPP_

#include "GraphicalStructures.hpp"
#include <memory>
#include <iostream>

namespace Arcade
{
    class IGraphicalModule
    {
    public:
        virtual ~IGraphicalModule() = default;

        virtual void drawText(graphical_text_t &text) = 0;

    };
}

#endif /* !IGRAPHICAL_MODULE_HPP_ */
