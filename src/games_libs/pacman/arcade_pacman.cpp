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

Arcade::Game_Pacman::Game_Pacman(): AGameModule(), _currentMapIndex(0)
{
}

Arcade::Game_Pacman::~Game_Pacman()
{

}

void Arcade::Game_Pacman::startGame()
{
    std::string path("ressources/pacman/maps/map_" + std::to_string(_currentMapIndex) + ".txt");
    _map = readFileIntoVector(path);
    graphical_sprite_t sprite;

    sprite.ncursesBox = 0;
    sprite.color = {0, 0, 255, {BLUE, BLACK}};
    sprite.id = 0;
    sprite.path = "ressources/pacman/wall.png";
    sprite.size = {20, 20, 0};
    float start_y = HEIGHT / 2 - (_map.size() / 2) * 19;
    float start_x = WIDTH / 2 - (_map[0].length() / 2) * 9.5;
    for (size_t y = 0; y < _map.size(); y += 1) {
        for (size_t x = 0; x < _map[y].length(); x += 1) {
            sprite.pos = {(float)start_x + x * 9.5, (float)start_y + y * 19, 0};
            if (_map[y][x] == '#' || _map[y][x] == '.' || _map[y][x] == '*') {
                sprite.path = (_map[y][x] == '#') ? "ressources/pacman/wall.png" : _map[y][x] == '.' ? "ressources/pacman/coins.png" : "ressources/pacman/star.png";
                sprite.id += 1;
                _sprites.push_back(sprite);
            }
        }
    }
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

int Arcade::Game_Pacman::updateGame(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list)
{
    for (auto &n : _sprites)
        _list->push_back(std::make_pair(SPRITE, &n));
    return (0);
}

extern "C" Arcade::IGameModule *entryPoint(void)
{
    return new Arcade::Game_Pacman;
}