/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** arcade_sdl2
*/

#ifndef ARCADE_SDL2_HPP_
#define ARCADE_SDL2_HPP_

#include "../../core/AGraphicalModule.hpp"
#include <SDL2/SDL.h>
#include "SDL_ttf.h"

namespace Arcade
{
    class Graphical_SDL2 : public AGraphicalModule {
        public:
            Graphical_SDL2();
            ~Graphical_SDL2();
            void drawText(graphical_text_t &text) final;
            void clear() final;
            void refresh() final;
            int check() final;
            void openWindow() final;
            void closeWindow() final;

        private:
            SDL_Window *_window = nullptr;
            SDL_Renderer *_renderer = nullptr;
            SDL_Event _event;

            int getInput();
    };
} // namespace Arcade

#endif /* !ARCADE_SDL2_HPP_ */
