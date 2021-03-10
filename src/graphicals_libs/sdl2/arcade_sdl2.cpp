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
    if (SDL_Init(SDL_INIT_VIDEO) < 0)     
    {         
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());         
        return;     
    }       
    SDL_Window* pWindow{ nullptr };     
    SDL_Renderer* pRenderer{ nullptr };       
    if (SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0)     
    {         
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());         
        SDL_Quit();         
        return;     
    }
    SDL_SetWindowTitle(pWindow, "Hello !");     
    SDL_Delay(1000); // mettre en pause pendant 1 seconde le rendu
    SDL_SetWindowTitle(pWindow, "World !");     
    SDL_Delay(1000);           
    SDL_DestroyRenderer(pRenderer);     
    SDL_DestroyWindow(pWindow);     
    SDL_Quit();       
}

void Arcade::Graphical_SDL2::closeWindow()
{

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