/*
** EPITECH PROJECT, 2021
** bootstrap_arcade
** File description:
** lib1
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "arcade_pacman.hpp"

Arcade::Game_Pacman::Game_Pacman(): AGameModule()
{
    _currentMapIndex = 0;
    initValues();
}

void Arcade::Game_Pacman::initValues()
{
    _pac.position[0] = 0;
    _pac.position[1] = 0;
    _pac.velocity = {0, 0, 0};
    _pac.previousVelocity = {0, 0, 0};
    _pac.previousPosition[0] = 0;
    _pac.previousPosition[1] = 0;
    _keyPressed = 0;
    _pac.buffer = {0, 0, 0};
    _start_y = 0;
    _start_x = 0;
    _score = 0;
}

Arcade::Game_Pacman::~Game_Pacman()
{

}

void Arcade::Game_Pacman::startGame()
{
    initValues();

    std::string path("ressources/pacman/maps/map_" + std::to_string(_currentMapIndex) + ".txt");
    _map = readFileIntoVector(path);
    graphical_sprite_t sprite;

    sprite.ncursesBox = 0;
    sprite.color = {0, 0, 255, {BLUE, BLACK}};
    sprite.id = 0;
    sprite.path = "ressources/pacman/wall.png";
    sprite.size = {20, 20, 0};
    _start_y = HEIGHT / 2 - (_map.size() / 2) * 19;
    _start_x = WIDTH / 2 - (_map[0].length() / 2) * 9.5;
    for (size_t y = 0; y < _map.size(); y += 1) {
        for (size_t x = 0; x < _map[y].length(); x += 1) {
            sprite.pos = {(float)_start_x + x * 9.5, (float)_start_y + y * 19, 0};
            if (_map[y][x] == '#' || _map[y][x] == '.' || _map[y][x] == '*') {
                sprite.path = (_map[y][x] == '#') ? "ressources/pacman/wall.png" : _map[y][x] == '.' ? "ressources/pacman/coins.png" : "ressources/pacman/star.png";
                sprite.id += 1;
                sprite.visible = 1;
                _sprites.push_back(sprite);
                continue;
            }
            sprite.visible = 0;
            if (_map[y][x] == 'S') {
                _pac.position[0] = x;
                _pac.position[1] = y;
                _pac.previousPosition[0] = x;
                _pac.previousPosition[1] = y;
            }
            _sprites.push_back(sprite);
        }
    }
    sprite.color = {255, 0, 0, {RED, BLACK}};
    sprite.id++;
    sprite.path = "ressources/pacman/pacman_up.png";
    _sprites.push_back(sprite);
    sprite.path = "ressources/pacman/pacman_down.png";
    sprite.id++;
    _sprites.push_back(sprite);
    sprite.path = "ressources/pacman/pacman_left.png";
    sprite.id++;
    _sprites.push_back(sprite);
    sprite.path = "ressources/pacman/pacman_right.png";
    sprite.id++;
    _sprites.push_back(sprite);
    _pac.velocity = {1, 0, 0};

    _box.input = _playerName;
    _box.size = {WIDTH / 10, HEIGHT / 15, 0};
    _box.pos = {WIDTH / 2, 100, 0};
}

std::vector<std::string> Arcade::Game_Pacman::readFileIntoVector(std::string filepath) const
{
    std::vector<std::string> res;
    std::ifstream file(filepath);
    std::string temp;

    if (file.is_open()) {
        while (std::getline(file, temp)) {
            res.push_back(temp);
        }
    }
    return (res);
}

bool Arcade::Game_Pacman::simulate()
{
    int proj_x = 0;
    int proj_y = 0;

    if (_pac.buffer.x != 0 || _pac.buffer.y != 0) {
        proj_x = _pac.position[0] + _pac.buffer.x;
        proj_y = _pac.position[1] + _pac.buffer.y;
        if (!((size_t)proj_y < _map.size() && (size_t)proj_x < _map[0].length() && (_map[proj_y][proj_x] == '#' || _map[proj_y][proj_x] == 'x'))) {
            _pac.previousVelocity = _pac.velocity;
            _pac.velocity = _pac.buffer;
            _pac.buffer = {0, 0, 0};
            return 1;
        }
    }
    proj_x = _pac.position[0] + _pac.velocity.x;
    proj_y = _pac.position[1] + _pac.velocity.y;
    if (!((size_t)proj_y < _map.size() && (size_t)proj_x < _map[0].length() && (_map[proj_y][proj_x] == '#' || _map[proj_y][proj_x] == 'x'))) {
        _pac.previousVelocity = _pac.velocity;
        return 1;
    }
    proj_x = _pac.position[0] + _pac.previousVelocity.x;
    proj_y = _pac.position[1] + _pac.previousVelocity.y;
    if (!((size_t)proj_y < _map.size() && (size_t)proj_x < _map[0].length() && (_map[proj_y][proj_x] == '#' || _map[proj_y][proj_x] == 'x'))) {
        _pac.velocity = _pac.previousVelocity;
        return 1;
    }
    return 0;
}

int Arcade::Game_Pacman::updateGame(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list)
{
    _pac.previousPosition[0] = _pac.position[0];
    _pac.previousPosition[1] = _pac.position[1];
    if (_keys[ARROW_DOWN] && !_keyPressed) {
        _keyPressed = 1;
        _pac.velocity = {0, 1, 0};
        _pac.buffer = {0, 1, 0};
    }
    if (_keys[ARROW_UP] && !_keyPressed) {
        _keyPressed = 1;
        _pac.velocity = {0, -1, 0};
        _pac.buffer = {0, -1, 0};
    }
    if (_keys[ARROW_RIGHT] && !_keyPressed) {
        _keyPressed = 1;
        _pac.velocity = {1, 0, 0};
        _pac.buffer = {1, 0, 0};
    }
    if (_keys[ARROW_LEFT] && !_keyPressed) {
        _keyPressed = 1;
        _pac.velocity = {-1, 0, 0};
        _pac.buffer = {-1, 0, 0};
    }
    bool status = simulate();
    if ((_pac.velocity.y != 0 && _mainClock.getElapsedTime() > 0.15) || (_pac.velocity.x != 0 && _mainClock.getElapsedTime() > 0.1)) {
        if (status) {
            _pac.position[0] += _pac.velocity.x;
            _pac.position[1] += _pac.velocity.y;
        }
        _mainClock.reset();
        _keyPressed = 0;
    }
    int i = _pac.position[1] * _map[0].length() + _pac.position[0];
    if (_sprites[i].visible) {
        _sprites[i].visible = 0;
        _score += 1;
    }
    draw(_list);
    return (0);
}

void Arcade::Game_Pacman::draw(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list)
{
    graphical_vector_t goodVelocity;
    int goodIndex = 0;

    for (int index = 0; index < _sprites.size() - 4; index += 1)
        if (_sprites[index].visible)
            _list->push_back(std::make_pair(SPRITE, &_sprites[index]));
    goodVelocity = ((_pac.velocity.x != 0 || _pac.velocity.y != 0) && !_keyPressed) ? _pac.velocity : _pac.previousVelocity;
    if (goodVelocity.x == 1) {
        goodIndex = _sprites.size() - 1;
    } else if (goodVelocity.x == -1) {
        goodIndex = _sprites.size() - 2;
    } else if (goodVelocity.y == 1)
        goodIndex = _sprites.size() - 3;
    else
        goodIndex = _sprites.size() - 4;
    graphical_sprite_t &sprite = _sprites[goodIndex];

    sprite.pos.x = _start_x + _pac.position[0] * 9.5;
    sprite.pos.y = _start_y + _pac.position[1] * 19;
    _list->push_back(std::make_pair(SPRITE, &sprite));
    _box.input = _playerName + " " + std::to_string(_score);
    _list->push_back(std::make_pair(BOX, &_box));
}

extern "C" Arcade::IGameModule *entryPoint(void)
{
    return new Arcade::Game_Pacman;
}