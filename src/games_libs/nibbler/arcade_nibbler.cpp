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
}

Arcade::Game_Nibbler::~Game_Nibbler()
{
}

void Arcade::Game_Nibbler::loadMap(int i)
{
    std::string path("ressources/nibbler/maps/map_" + std::to_string(i) + ".txt");
    std::vector<std::string> map = readFileIntoVector(path);
    std::size_t index = 1;
    graphical_sprite_t sprite;

    sprite.visible = 1;
    sprite.ncursesBox = 0;
    sprite.path = "ressources/nibbler/wall.png";
    sprite.color = {255, 0, 0, {YELLOW, YELLOW}};
    sprite.size = {40, 40, 0};
    sprite.angle = 0;
    for (size_t y = 0; y < map.size(); y++) {
        for (size_t x = 0; x < map[y].length(); x++) {
            if (map[y][x] == '#') {
                sprite.id = index;
                index += 1;
                sprite.pos = {(WIDTH / 2 - 40 * 10) + x * 40 + 20, (HEIGHT / 2 - 40 * 10) + y * 40 + 20, 0};
                _sprites.push_back(sprite);
                _wall.push_back({x, y, 0});
            }
        }
    }
}

std::vector<std::string> Arcade::Game_Nibbler::readFileIntoVector(std::string filepath) const
{
    std::vector<std::string> res;
    std::ifstream file(filepath);
    std::string temp;

    if (file.is_open()) {
        while (std::getline(file, temp)) {
            res.push_back(temp);
        }
        file.close();
    }
    return (res);
}

void Arcade::Game_Nibbler::startGame()
{
    _snake.clear();
    _wall.clear();
    appleNewPos();
    _speed = {1, 0, 0};
    _score = 0;
    graphical_text_t text;

    text.color = {0, 255, 0, {GREEN, BLACK}};
    text.font = "ressources/font.ttf";
    text.id = 0;
    text.size = 30;
    text.pos = {WIDTH / 2, 50, 0};
    _texts.push_back(text);
    _indexsnake = 200;
    graphical_sprite_t sprite;

    sprite.visible = 1;
    sprite.ncursesBox = 0;
    sprite.id = 0;
    sprite.path = "ressources/nibbler/snake_apple.png";
    sprite.color = {255, 0, 0, {RED, RED}};
    sprite.pos = {(WIDTH / 2 - 40 * 10) + _apple.x * 40 + 20, (HEIGHT / 2 - 40 * 10) + _apple.y * 40 + 20, 0};
    sprite.size = {40, 40, 0};
    sprite.angle = 0;
    _sprites.push_back(sprite);
    loadMap(0);
    sprite.path = "ressources/nibbler/snake_tail.png";
    sprite.color = {0, 255, 0, {GREEN, GREEN}};
    sprite.size = {40, 40, 0};
    for (float i = 0; i < 4; i++) {
        _snake.push_back({7 - i, 7, 0});
        sprite.pos = {(WIDTH / 2 - 40 * 10) + _snake[_indexsnake-200].x * 40 + 20, (HEIGHT / 2 - 40 * 10) + _snake[_indexsnake-200].y * 40 + 20, 0};
        sprite.id = _indexsnake++;
        _sprites.push_back(sprite);
    }
}

void Arcade::Game_Nibbler::appleNewPos()
{
    _apple.x = rand() % 20;
    _apple.y = rand() % 20;
    for (std::size_t i = 0; i < _wall.size(); i++)
        if (_apple.x == _wall[i].x && _apple.y == _wall[i].y)
            appleNewPos();
    for (std::size_t i = 0; i < _snake.size(); i++)
        if (_apple.x == _snake[i].x && _apple.y == _snake[i].y)
            appleNewPos();
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
    if (_mainClock.getElapsedTime() > 0.2) {
        _keyPressed = false;
        graphical_vector_t tmp = _snake[_snake.size() - 1];
        for (int i = _snake.size() - 1; i > 0; i--) {
            _snake[i].x = _snake[i-1].x;
            _snake[i].y = _snake[i-1].y;
        }
        _snake[0].x += _speed.x;
        _snake[0].y += _speed.y;
        if (_snake[0].x == _apple.x && _snake[0].y == _apple.y) {
            _score++;
            appleNewPos();
            _snake.push_back(tmp);
            graphical_sprite_t sprite;
            sprite.visible = 1;
            sprite.ncursesBox = 0;
            sprite.path = "ressources/nibbler/snake_tail.png";
            sprite.color = {0, 255, 0, {GREEN, GREEN}};
            sprite.pos = {(WIDTH / 2 - 40 * 10) + _snake[_indexsnake-200].x * 40 + 20, (HEIGHT / 2 - 40 * 10) + _snake[_indexsnake-200].y * 40 + 20, 0};
            sprite.size = {40, 40, 0};
            sprite.angle = 0;
            sprite.id = _indexsnake++;
            _sprites.push_back(sprite);
        }
        _mainClock.reset();
    }
    if (checkDeath()) {
        _sprites.clear();
        _texts.clear();
        startGame();
    }
    draw(list);
    return (0);
}

void Arcade::Game_Nibbler::draw(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *list)
{
    int index = 0;
    for (size_t i = 0; i < _sprites.size(); i++)
        if (_sprites[i].id >= 200) {
            _sprites[i].pos = {(WIDTH / 2 - 40 * 10) + _snake[index].x * 40 + 20, (HEIGHT / 2 - 40 * 10) + _snake[index].y * 40 + 20, 0};
            index++;
        }
    _sprites[0].pos = {(WIDTH / 2 - 40 * 10) + _apple.x * 40 + 20, (HEIGHT / 2 - 40 * 10) + _apple.y * 40 + 20, 0};
    for (auto &n : _sprites)
        list->push_back(std::make_pair(SPRITE, &n));
    _texts[0].text = std::to_string(_score);
    for (auto &n : _texts)
        list->push_back(std::make_pair(TEXT, &n));
}

bool Arcade::Game_Nibbler::checkDeath()
{
    for (std::size_t i = _snake.size() - 1; i > 0; i--)
        if (_snake[0].x == _snake[i].x && _snake[0].y == _snake[i].y)
            return true;
    for (std::size_t i = 0; i < _wall.size(); i++)
        if (_snake[0].x == _wall[i].x && _snake[0].y == _wall[i].y)
            return true;
    if (_snake.size() == 15 * 15)
        return true;
    return false;
}

extern "C" Arcade::IGameModule *entryPoint(void)
{
    return new Arcade::Game_Nibbler;
}