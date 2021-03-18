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
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <unordered_map>

namespace Arcade
{
    class Graphical_SDL2 : public AGraphicalModule {
        public:
            Graphical_SDL2();
            ~Graphical_SDL2();
            void drawText(graphical_text_t &text) final;
            void drawSprite(graphical_sprite_t &sprite) final;
            void showInputBox(graphical_box_t &box) final;
            void reset() final;
            void clear() final;
            void refresh() final;
            void updateInputsMap() final;
            void openWindow() final;
            void closeWindow() final;

        private:
            SDL_Window *_window = nullptr;
            SDL_Renderer *_renderer = nullptr;
            SDL_Event _event;
            TTF_Font *_font = nullptr;
            std::unordered_map<unsigned int, bool> _key;
            std::unordered_map<unsigned int, std::pair<SDL_Texture *, graphical_vector_t>> _sprites;
            std::unordered_map<unsigned int, std::pair<SDL_Texture *, graphical_text_t>> _texts;
            int getInput();
    };
} // namespace Arcade

#endif /* !ARCADE_SDL2_HPP_ */
