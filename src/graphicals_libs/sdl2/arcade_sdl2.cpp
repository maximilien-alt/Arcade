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
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, &_window, &_renderer);
    SDL_SetWindowTitle(_window, "Arcade");
    TTF_Init();
    _font = TTF_OpenFont("ressources/font.ttf", 200);
}

void Arcade::Graphical_SDL2::closeWindow()
{
    if (!_renderer)
        return;
    reset();
    SDL_DestroyRenderer(_renderer);
    _renderer = nullptr;
    SDL_DestroyWindow(_window);
    if (_font)
        TTF_CloseFont(_font);
    TTF_Quit();
}

void Arcade::Graphical_SDL2::drawSprite(graphical_sprite_t &sprite)
{
    if (!_renderer)
        return;
    graphical_vector_t size = {0, 0, 0};
    if (_sprites.find(sprite.id) == _sprites.end())
    {
        SDL_Texture *img = IMG_LoadTexture(_renderer, sprite.path.c_str());
        int w, h;
        SDL_QueryTexture(img, NULL, NULL, &w, &h);
        size.x = w;
        size.y = h;
        _sprites[sprite.id] = std::make_pair(img, size);
    }
    size = _sprites[sprite.id].second;
    SDL_Rect texr;
    texr.x = sprite.pos.x - size.x / 2;
    texr.y = sprite.pos.y - size.y / 2;
    texr.w = size.x;
    texr.h = size.y;

    SDL_RenderCopy(_renderer, _sprites[sprite.id].first, NULL, &texr);
}

void Arcade::Graphical_SDL2::drawText(graphical_text_t &text)
{
    if (!_renderer)
        return;
    SDL_Color textColor = {text.color.r, text.color.g, text.color.b, 255};

    if (_texts.find(text.id) != _texts.end())
    {
        if (text.text != _texts[text.id].second.text || textColor.r != _texts[text.id].second.color.r || textColor.g != _texts[text.id].second.color.g || textColor.b != _texts[text.id].second.color.b)
        {
            SDL_DestroyTexture(_texts[text.id].first);
            _texts.erase(text.id);
        }
    }
    if (_texts.find(text.id) == _texts.end())
    {
        SDL_Surface *surfaceText = TTF_RenderText_Solid(_font, text.text.c_str(), textColor);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surfaceText);
        _texts[text.id] = std::make_pair(texture, text);
    }
    SDL_Rect rect;
    rect.x = text.pos.x;
    rect.y = text.pos.y;
    rect.w = text.text.length() * (text.size * 2 / 4);
    rect.h = text.size + 4;

    SDL_RenderCopy(_renderer, _texts[text.id].first, NULL, &rect);
}

void Arcade::Graphical_SDL2::clear()
{
    for (auto &key : _key)
    {
        key.second = false;
    }
    while (SDL_PollEvent(&_event))
    {
        if (_event.type == SDL_QUIT)
        {
            closeWindow();
            return;
        }
        if (_event.type == SDL_KEYDOWN)
        {
            _key[_event.key.keysym.sym] = true;
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
    const SDL_Rect rect = {(int)(box.pos.x - box.size.x / 2), (int)(box.pos.y - box.size.y / 2), (int)box.size.x, (int)box.size.y};

    graphical_text_t text;
    text.id = 999;
    text.text = box.input;
    text.pos = (graphical_vector_t){(float)(rect.x + 18), box.pos.y - 48, 0};
    text.size = 18;
    text.color = (graphical_color_t){255, 255, 255, {WHITE, WHITE}};
    text.font = "ressources/font.ttf";
    drawText(text);
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(_renderer, &rect);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderPresent(_renderer);
}

void Arcade::Graphical_SDL2::updateInputsMap()
{
    for (int index = SDLK_F1; index <= SDLK_F7; index += 1)
        if (_key[index])
            _keys[index - SDLK_F1] = 1;
    for (int index = SDLK_a; index <= SDLK_z; index += 1)
        if (_key[index])
            _keys[index - SDLK_a + Arcade::KEYS::A] = 1;
    _keys[Arcade::KEYS::ARROW_LEFT] = _key[SDLK_LEFT];
    _keys[Arcade::KEYS::ARROW_RIGHT] = _key[SDLK_RIGHT];
    _keys[Arcade::KEYS::ARROW_UP] = _key[SDLK_UP];
    _keys[Arcade::KEYS::ARROW_DOWN] = _key[SDLK_DOWN];
    _keys[Arcade::KEYS::BACKSPACE] = _key[SDLK_BACKSPACE];
}

void Arcade::Graphical_SDL2::reset()
{
    for (auto &texture : _sprites)
    {
        SDL_DestroyTexture(texture.second.first);
    }
    _sprites.clear();
    for (auto &texture : _texts)
    {
        SDL_DestroyTexture(texture.second.first);
    }
    _texts.clear();
}

extern "C" Arcade::IGraphicalModule *entryPoint()
{
    return new Arcade::Graphical_SDL2;
}