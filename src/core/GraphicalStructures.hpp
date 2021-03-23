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
    enum COLOR {
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE
    };

    enum KEYS {
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        BACKSPACE,
        ARROW_LEFT,
        ARROW_UP,
        ARROW_RIGHT,
        ARROW_DOWN,
        NONE
    };

    enum FLAGS
    {
        SPRITE,
        TEXT,
        BOX
    };

    typedef struct IStruct_s
    {
        virtual ~IStruct_s() = default;
    } IStruct_t;

    typedef struct graphical_vector_s
    {
        float x;
        float y;
        float z;
    } graphical_vector_t;

    typedef struct graphical_color_s
    {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        Arcade::COLOR ncurse[2];
    } graphical_color_t;

    typedef struct graphical_text_s: IStruct_t
    {
        unsigned int id;
        std::string text;
        graphical_vector_t pos;
        int size;
        graphical_color_t color;
        std::string font;
    } graphical_text_t;

    typedef struct graphical_sprite_s: IStruct_t
    {
        unsigned int id;
        std::string path;
        bool ncursesBox;
        graphical_color_t color;
        graphical_vector_t pos;
        graphical_vector_t size;
    } graphical_sprite_t;

    typedef struct graphical_box_s: IStruct_t
    {
        graphical_vector_t pos;
        graphical_vector_t size;
        std::string input;
    } graphical_box_t;
}

#endif /* !GRAPHICALSTRUCTURES_HPP_ */
