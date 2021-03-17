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
    SDL_Quit();
}

void Arcade::Graphical_SDL2::openWindow()
{
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &_window, &_renderer);
    SDL_SetWindowTitle(_window, "SDL window");
    TTF_Init();
    _font = TTF_OpenFont("ressources/font.ttf", 200);

}

void Arcade::Graphical_SDL2::closeWindow()
{
    reset();
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    TTF_CloseFont(_font);
    TTF_Quit();
}

void Arcade::Graphical_SDL2::drawSprite(graphical_sprite_t &sprite)
{
    int w, h;
    if (_sprites.find(sprite.id) == _sprites.end()) {
        SDL_Texture *img = IMG_LoadTexture(_renderer, sprite.path.c_str());
        SDL_QueryTexture(img, NULL, NULL, &w, &h);
        _sprites[sprite.id] = img;
    }

    SDL_Rect texr;
    texr.x = WIDTH / 2;
    texr.y = HEIGHT / 2;
    texr.w = w * 2;
    texr.h = h * 2;

    SDL_RenderCopy(_renderer, _sprites[sprite.id], NULL, &texr);
    SDL_DestroyTexture(_sprites[sprite.id]);
}

void Arcade::Graphical_SDL2::drawText(graphical_text_t &text)
{
    SDL_Color textColor = {text.color.r, text.color.g, text.color.b, 255};

    if (_texts.find(text.id) != _texts.end()) {
        if (text.text != _texts[text.id].second.text || textColor.r != _texts[text.id].second.color.r || textColor.g != _texts[text.id].second.color.g || textColor.b != _texts[text.id].second.color.b) {
            SDL_DestroyTexture(_texts[text.id].first);
            _texts.erase(text.id);
        }
    }
    if (_texts.find(text.id) == _texts.end()) {
        SDL_Surface *surfaceText = TTF_RenderText_Solid(_font, text.text.c_str(), textColor);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surfaceText);
        _texts[text.id] = std::make_pair(texture, text);
    }
    SDL_Rect rect;
    rect.x = text.pos.x;
    rect.y = text.pos.y;
    rect.w = text.text.length() * (text.size * 2 / 3);
    rect.h = text.size + 4;

    SDL_RenderCopy(_renderer, _texts[text.id].first, NULL, &rect);
}

void Arcade::Graphical_SDL2::clear()
{
    while (SDL_PollEvent(&_event)) {
        if (_event.type == SDL_QUIT) {
            closeWindow();
        }
    }
    SDL_RenderClear(_renderer);
}

void Arcade::Graphical_SDL2::refresh()
{
    SDL_RenderPresent(_renderer);
}

void Arcade::Graphical_SDL2::showInputBox(graphical_box_t &box)
{
    (void)box;
}

int Arcade::Graphical_SDL2::check()
{
    int input = getInput();

    switch (input) {
        case SDLK_F1:
            return (1);
        case SDLK_F2:
            return (2);
        case SDLK_F3:
            return (3);
        case SDLK_F4:
            return (4);
        case SDLK_F5:
            return (5);
        case SDLK_F6:
            return (6);
        case SDLK_F7:
            return (7);
        default:
            return (0);
    }
    return (0);
}

void Arcade::Graphical_SDL2::reset()
{
    for (auto &texture : _sprites) {
        SDL_DestroyTexture(texture.second);
    }
    _sprites.clear();
    for (auto &texture : _texts) {
        SDL_DestroyTexture(texture.second.first);
    }
    _texts.clear();
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