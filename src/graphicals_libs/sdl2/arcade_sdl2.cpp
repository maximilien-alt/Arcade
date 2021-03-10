/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** arcade_SDL2
*/

#include "arcade_sdl2.hpp"

Arcade::Graphical_SDL2::Graphical_SDL2() : AGraphicalModule()
{
}

Arcade::Graphical_SDL2::~Graphical_SDL2()
{
}

void Arcade::Graphical_SDL2::openWindow()
{
    _window = nullptr;
    _renderer = nullptr;
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &_window, &_renderer);
    SDL_SetWindowTitle(_window, "SDL window");
}

void Arcade::Graphical_SDL2::closeWindow()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Arcade::Graphical_SDL2::drawText(graphical_text_t &text)
{
}

void Arcade::Graphical_SDL2::clear()
{
}

void Arcade::Graphical_SDL2::refresh()
{
}

int Arcade::Graphical_SDL2::check()
{
    return (0);
}

int Arcade::Graphical_SDL2::getInput()
{
    return (0);
}

extern "C" Arcade::IGraphicalModule *entryPoint()
{
    return new Arcade::Graphical_SDL2;
}