/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** AGameModule
*/

#include "AGameModule.hpp"

Arcade::AGameModule::AGameModule()
{
    _box.pos = {0, 0, 0};
    _box.size = {0, 0, 0};
}

void Arcade::AGameModule::setKeys(std::unordered_map<int, bool> keys)
{
    _keys = keys;
}

void Arcade::AGameModule::setMousePosition(graphical_vector_t pos)
{
    _mousePosition = pos;
}

bool Arcade::AGameModule::isMouseOnSpriteHitbox(graphical_sprite_t sprite)
{
    return (!(_mousePosition.y < sprite.pos.y - sprite.size.y  / 2 || \
            _mousePosition.y > sprite.pos.y + sprite.size.y  / 2|| \
            _mousePosition.x < sprite.pos.x - sprite.size.x  / 2|| \
            _mousePosition.x > sprite.pos.x + sprite.size.x / 2));
}