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
    _currentMapIndex = 0;
}

Arcade::Game_Nibbler::~Game_Nibbler()
{
}

void Arcade::Game_Nibbler::loadMap()
{
    _sprites.clear();
    _texts.clear();
    std::string path("ressources/nibbler/maps/map_" + std::to_string(_currentMapIndex) + ".txt");
    std::vector<std::string> map = readFileIntoVector(path);
    unsigned int indexwall = TEXTURE_WALL_ID;
    unsigned int indexapple = TEXTURE_APPLE_ID;
    graphical_text_t text;

    text.color = {0, 255, 0, {GREEN, BLACK}};
    text.font = "ressources/font.ttf";
    text.id = 0;
    text.size = 30;
    text.pos = {WIDTH / 2, 50, 0};
    _texts.push_back(text);
    _timeleft = std::stoi(map[0]);

    text.color = {0, 255, 0, {RED, BLACK}};
    text.font = "ressources/font.ttf";
    text.id = 1;
    text.size = 30;
    text.pos = {WIDTH / 2 + 40 * 8, 50, 0};
    _texts.push_back(text);

    _snake.clear();
    _wall.clear();
    _apple.clear();
    _speed = {1, 0, 0};
    _speedbuffer = {1, 0, 0};
    _toGrow = 0;
    graphical_sprite_t sprite;

    sprite.visible = 1;
    sprite.ncursesBox = 0;
    sprite.size = {40, 40, 0};
    sprite.angle = 0;
    for (size_t y = 1; y < map.size(); y++) {
        for (size_t x = 0; x < map[y].length(); x++) {
            if (map[y][x] == 'A') {
                sprite.path = "ressources/nibbler/apple.png";
                sprite.color = {255, 0, 0, {GREEN, RED}};
                sprite.id = indexapple++;
                sprite.pos = {(float)((WIDTH / 2 - 40 * 10) + x * 40 + 20), (float)((HEIGHT / 2 - 40 * 10) + (y - 1) * 40 + 20), 0};
                _sprites.push_back(sprite);
                _apple.push_back({(float)x, (float)(y - 1), 0});
            }
        }
    }
    for (size_t y = 1; y < map.size(); y++) {
        for (size_t x = 0; x < map[y].length(); x++) {
            if (map[y][x] == '#') {
                sprite.path = "ressources/nibbler/wall.png";
                sprite.color = {255, 255, 0, {YELLOW, YELLOW}};
                sprite.id = indexwall++;
                sprite.pos = {(float)((WIDTH / 2 - 40 * 10) + x * 40 + 20), (float)((HEIGHT / 2 - 40 * 10) + (y - 1) * 40 + 20), 0};
                _sprites.push_back(sprite);
                _wall.push_back({(float)x, (float)(y - 1), 0});
            }
        }
    }
    _indexsnake = TEXTURE_SNAKE_ID;
    sprite.path = "ressources/nibbler/snake_head.png";
    sprite.color = {0, 0, 255, {MAGENTA, BLUE}};
    _snake.push_back({7, 9, 0});
    sprite.pos = {(WIDTH / 2 - 40 * 10) + _snake[_indexsnake-TEXTURE_SNAKE_ID].x * 40 + 20, (HEIGHT / 2 - 40 * 10) + _snake[_indexsnake-TEXTURE_SNAKE_ID].y * 40 + 20, 0};
    sprite.id = _indexsnake++;
    _sprites.push_back(sprite);
    sprite.color = {0, 255, 0, {GREEN, MAGENTA}};
    sprite.path = "ressources/nibbler/snake_tail.png";
    for (float i = 1; i < 4; i++) {
        _snake.push_back({7 - i, 9, 0});
        sprite.pos = {(WIDTH / 2 - 40 * 10) + _snake[_indexsnake-TEXTURE_SNAKE_ID].x * 40 + 20, (HEIGHT / 2 - 40 * 10) + _snake[_indexsnake-TEXTURE_SNAKE_ID].y * 40 + 20, 0};
        sprite.id = _indexsnake++;
        _sprites.push_back(sprite);
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

void Arcade::Game_Nibbler::initValues()
{
    _score = 0;
}

void Arcade::Game_Nibbler::startGame()
{
    initValues();
    loadMap();
}

int Arcade::Game_Nibbler::updateGame(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *list)
{
    float clockSpeed = 0.2;

    if (_keys[ARROW_DOWN] && _speed.y != -1 && !_keyPressed) {
        _speedbuffer = {0, 1, 0};
        _keyPressed = true;
    }
    if (_keys[ARROW_UP] && _speed.y != 1 && !_keyPressed) {
        _speedbuffer = {0, -1, 0};
        _keyPressed = true;
    }
    if (_keys[ARROW_LEFT] && _speed.x != 1 && !_keyPressed) {
        _speedbuffer = {-1, 0, 0};
        _keyPressed = true;
    }
    if (_keys[ARROW_RIGHT] && _speed.x != -1 && !_keyPressed) {
        _speedbuffer = {1, 0, 0};
        _keyPressed = true;
    }
    if (!checkWall(_speedbuffer.x, _speedbuffer.y))
        _speed = _speedbuffer;
    if (_keys[SPACE])
        clockSpeed = 0.05;
    if (_timeClock.getElapsedTime() > 1) {
        _timeClock.reset();
        _timeleft -= 1;
    }
    if (_mainClock.getElapsedTime() > clockSpeed) {
        _keyPressed = false;
        if (!checkWall(_speed.x, _speed.y)) {
            graphical_vector_t tmp = _snake[_snake.size() - 1];
            for (int i = _snake.size() - 1; i > 0; i--) {
                _snake[i].x = _snake[i-1].x;
                _snake[i].y = _snake[i-1].y;
            }
            _snake[0].x += _speed.x;
            _snake[0].y += _speed.y;
            for (unsigned int i = 0; i < _apple.size(); i++) {
                if (_snake[0].x == _apple[i].x && _snake[0].y == _apple[i].y) {
                    _toGrow += rand() % 3 + 1;
                    _score++;
                _apple.erase(_apple.begin() + i);
                _sprites.erase(_sprites.begin() + i);
                }
            }
            if (_toGrow > 0) {
                _toGrow -= 1;
                _snake.push_back(tmp);
                graphical_sprite_t sprite;
                sprite.visible = 1;
                sprite.ncursesBox = 0;
                sprite.path = "ressources/nibbler/snake_tail.png";
                sprite.color = {0, 255, 0, {GREEN, MAGENTA}};
                sprite.pos = {(WIDTH / 2 - 40 * 10) + _snake[_indexsnake-TEXTURE_SNAKE_ID].x * 40 + 20, (HEIGHT / 2 - 40 * 10) + _snake[_indexsnake-TEXTURE_SNAKE_ID].y * 40 + 20, 0};
                sprite.size = {40, 40, 0};
                sprite.angle = 0;
                sprite.id = _indexsnake++;
                _sprites.push_back(sprite);
            }
        }
        _mainClock.reset();
    }
    if (checkWin()) {
        _currentMapIndex = (_currentMapIndex + 1) % 2;
        loadMap();
    }
    if (checkDeath()) {
        _sprites.clear();
        _texts.clear();
        newScore();
        startGame();
    }
    draw(list);
    return (0);
}

void Arcade::Game_Nibbler::newScore() const
{
    std::string path("ressources/nibbler/highscore.txt");
    std::ofstream file(path, std::ios_base::app);

    file << (_playerName == "" ? "user" : _playerName) << " " << _score << std::endl;
    file.close();
}

void Arcade::Game_Nibbler::draw(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *list)
{
    int index = 0;
    for (size_t i = 0; i < _sprites.size(); i++)
        if (_sprites[i].id >= TEXTURE_SNAKE_ID) {
            _sprites[i].angle = _speed.y == -1 ? 0 : _sprites[i].angle;
            _sprites[i].angle = _speed.y == 1 ? 180 : _sprites[i].angle;
            _sprites[i].angle = _speed.x == 1 ? 90 : _sprites[i].angle;
            _sprites[i].angle = _speed.x == -1 ? 270 : _sprites[i].angle;
            _sprites[i].pos = {(WIDTH / 2 - 40 * 10) + _snake[index].x * 40 + 20, (HEIGHT / 2 - 40 * 10) + _snake[index].y * 40 + 20, 0};
            index++;
        }
    for (auto &n : _sprites)
        list->push_back(std::make_pair(SPRITE, &n));
    _texts[0].text = std::to_string(_score);
    _texts[1].text = std::to_string(_timeleft);
    for (auto &n : _texts)
        list->push_back(std::make_pair(TEXT, &n));
}

bool Arcade::Game_Nibbler::checkWall(int x, int y)
{
    for (std::size_t i = 0; i < _wall.size(); i++)
        if (_snake[0].x + x == _wall[i].x && _snake[0].y + y == _wall[i].y)
            return true;
    return false;
}

bool Arcade::Game_Nibbler::checkWin()
{
    if (_apple.size() == 0)
        return true;
    return false;
}

bool Arcade::Game_Nibbler::checkDeath()
{
    if (_timeleft == 0)
        return true;
    for (std::size_t i = _snake.size() - 1; i > 0; i--)
        if (_snake[0].x == _snake[i].x && _snake[0].y == _snake[i].y)
            return true;
    if (_snake.size() + _wall.size() == 20 * 20)
        return true;
    return false;
}

extern "C" Arcade::IGameModule *entryPoint(void)
{
    return new Arcade::Game_Nibbler;
}