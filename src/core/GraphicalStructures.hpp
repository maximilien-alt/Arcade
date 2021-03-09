/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** graphicalStructures
*/

#ifndef GRAPHICALSTRUCTURES_HPP_
#define GRAPHICALSTRUCTURES_HPP_

#include <string>

namespace Arcade
{
    typedef struct graphical_pos_s
    {
        float x;
        float y;
        float z;
    } graphical_pos_t;

    typedef struct graphical_color_s
    {
        unsigned char r;
        unsigned char g;
        unsigned char b;
    } graphical_color_t;

    typedef struct graphical_text_s
    {
        std::string text;
        graphical_pos_t pos;
        int size;
        graphical_color_t color;
    } graphical_text_t;
}

#endif /* !GRAPHICALSTRUCTURES_HPP_ */
