/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** IGRAPHICAL_MODULE
*/

#ifndef IGRAPHICAL_MODULE_HPP_
#define IGRAPHICAL_MODULE_HPP_

#include <ncurses.h>

#define WIDTH 1920
#define HEIGHT 1080
#define product_x(x) (COLS * x / WIDTH)
#define product_y(y) (LINES * y / HEIGHT)

#include "GraphicalStructures.hpp"
#include "Tools.hpp"
#include "AStar.hpp"
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <string>

namespace Arcade
{
    class IGraphicalModule
    {
    public:
        virtual ~IGraphicalModule() = default;

        virtual void drawText(graphical_text_t &text) = 0;
        virtual void drawSprite(graphical_sprite_t &sprite) = 0;
        virtual void showInputBox(graphical_box_t &box) = 0;
        virtual std::unordered_map<int, bool> getInputsMap() const = 0;
        virtual void resetKeys() = 0;
        virtual void reset() = 0;
        virtual void clear() = 0;
        virtual void refresh() = 0;
        virtual void updateInputsMap() = 0;
        virtual void openWindow() = 0;
        virtual void closeWindow() = 0;
        virtual bool isMouseClicked() = 0;
        virtual graphical_vector_t getMousePosition() = 0;
    };
}

#endif /* !IGRAPHICAL_MODULE_HPP_ */