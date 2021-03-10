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
    int input = getInput();

    switch(input) {
        case SDLK_a:
            return (1);
        case SDLK_z:
            return (2);
        case SDLK_e:
            return (3);
        case SDLK_r:
            return (4);
        case SDLK_t:
            return (5);
        case SDLK_y:
            return (6);
        case SDLK_u:
            return (7);
        default:
            return (0);
    }
    return (0);
}

int Arcade::Graphical_SDL2::getInput()
{
    if (SDL_PollEvent(&_event)) {
        if (_event.type == SDL_KEYDOWN) {
            return (_event.key.keysym.sym);
        }
    }
    return (0);
}

extern "C" Arcade::IGraphicalModule *entryPoint()
{
    return new Arcade::Graphical_SDL2;
}