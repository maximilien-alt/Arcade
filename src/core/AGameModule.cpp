/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** AGameModule
*/

#include "AGameModule.hpp"

Arcade::AGameModule::AGameModule(): _mouseClicked(0)
{
    _box.pos = {0, 0, 0};
    _box.size = {0, 0, 0};
}

void Arcade::AGameModule::setKeys(std::unordered_map<int, bool> keys)
{
    _keys = keys;
}

void Arcade::AGameModule::setMouseClickedStatus(bool status)
{
    _mouseClicked = status;
}

void Arcade::AGameModule::setMousePosition(graphical_vector_t pos)
{
    _mousePosition = pos;
}

bool Arcade::AGameModule::isMouseClickedOnSprite(graphical_sprite_t sprite)
{

    if (_mouseClicked) {
        std::cout << sprite.path << std::endl;
        std::cout << "mousePosition: y: " << _mousePosition.y << "| x: " << _mousePosition.x << std::endl;
        std::cout << "spritePosition: y: " << sprite.pos.y << "| x: " << sprite.pos.x << std::endl;
        std::cout << "spriteSize: y: " << sprite.size.y << "| x: " << sprite.size.x << std::endl;
        return (_mousePosition.y >= sprite.pos.y - sprite.size.y / 2 && \
                _mousePosition.y <= sprite.pos.y + sprite.size.y / 2 && \
                _mousePosition.x >= sprite.pos.x - sprite.size.x / 2 && \
                _mousePosition.x <= sprite.pos.x + sprite.size.x / 2);
    }/* else
        std::cout << "not clicked mouse" << std::endl;*/
    return 0;
}

void Arcade::AGameModule::runClock()
{
    _tick = false;
    _clock++;
    if (_clock >= _fps) {
        _tick = true;
        _clock = 0;
    }
}