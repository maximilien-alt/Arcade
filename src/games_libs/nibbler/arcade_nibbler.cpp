/*
** EPITECH PROJECT, 2021
** bootstrap_arcade
** File description:
** lib1
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "arcade_nibbler.hpp"

Arcade::Game_Nibbler::Game_Nibbler(): AGameModule()
{
    _box.pos = {WIDTH / 2, HEIGHT / 2, 0};
    _box.size = {40 * 15, 40 * 15, 0};
    _apple = {-1, 0, 0};
    _speed = {1, 0, 0};
    _snake.push_back({7, 7, 0});
    _snake.push_back({6, 7, 0});
    _snake.push_back({5, 7, 0});
    _snake.push_back({4, 7, 0});
}

Arcade::Game_Nibbler::~Game_Nibbler()
{

}

void Arcade::Game_Nibbler::startGame()
{
}

int Arcade::Game_Nibbler::updateGame(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *list)
{
    if (_keys[ARROW_DOWN] && _speed.y != -1 && !_keyPressed) {
        _speed = {0, 1, 0};
        _keyPressed = true;
    }
    if (_keys[ARROW_UP] && _speed.y != 1 && !_keyPressed) {
        _speed = {0, -1, 0};
        _keyPressed = true;
    }
    if (_keys[ARROW_LEFT] && _speed.x != 1 && !_keyPressed) {
        _speed = {-1, 0, 0};
        _keyPressed = true;
    }
    if (_keys[ARROW_RIGHT] && _speed.x != -1 && !_keyPressed) {
        _speed = {1, 0, 0};
        _keyPressed = true;
    }
    if (_apple.x == -1) {
        _apple.x = rand() % 15;
        _apple.y = rand() % 15;
    }
    if (_tick) {
        _keyPressed = false;
        graphical_vector_t tmp = _snake[_snake.size() - 1];
        for (int i = _snake.size() - 1; i > 0; i--) {
            _snake[i].x = _snake[i-1].x;
            _snake[i].y = _snake[i-1].y;
        }
        _snake[0].x += _speed.x;
        _snake[0].y += _speed.y;
        if (_snake[0].x == _apple.x && _snake[0].y == _apple.y) {
            _apple.x = -1;
            _snake.push_back(tmp);
        }
    }
    if (checkDeath()) {
        _snake.clear();
        _apple = {-1, 0, 0};
        _speed = {1, 0, 0};
        _snake.push_back({7, 7, 0});
        _snake.push_back({6, 7, 0});
        _snake.push_back({5, 7, 0});
        _snake.push_back({4, 7, 0});
    }
    draw(list);
}

void Arcade::Game_Nibbler::draw(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *list)
{
    _sprites.clear();
    for (auto snake : _snake) {
        graphical_sprite_t sprite;
        sprite.id = _indexsprite++;
        sprite.path = "ressources/snake_tail.png";
        sprite.color = {0, 255, 0, {GREEN, GREEN}};
        sprite.pos = {(_box.pos.x - _box.size.x / 2) + snake.x * 40, (_box.pos.y - _box.size.y / 2) + snake.y * 40, 0};
        sprite.size = {40, 40, 0};
        _sprites.push_back(sprite);
    }
    if (_apple.x != -1) {
        graphical_sprite_t sprite;
        sprite.id = _indexsprite++;
        sprite.path = "ressources/snake_apple.png";
        sprite.color = {255, 0, 0, {RED, RED}};
        sprite.pos = {(_box.pos.x - _box.size.x / 2) + _apple.x * 40, (_box.pos.y - _box.size.y / 2) + _apple.y * 40, 0};
        sprite.size = {40, 40, 0};
        _sprites.push_back(sprite);
    }
    list->push_back(std::make_pair(BOX, &_box));
    for (auto &n : _sprites)
        list->push_back(std::make_pair(SPRITE, &n));
}

bool Arcade::Game_Nibbler::checkDeath()
{
    for (int i = _snake.size() - 1; i > 0; i--)
        if (_snake[0].x == _snake[i].x && _snake[0].y == _snake[i].y)
            return true;
    if (_snake[0].x < 0 || _snake[0].x >= 15 || _snake[0].y < 0 || _snake[0].y >= 15)
        return true;
    if (_snake.size() == 15 * 15)
        return true;
    return false;
}

extern "C" Arcade::IGameModule *entryPoint(void)
{
    return new Arcade::Game_Nibbler;
}