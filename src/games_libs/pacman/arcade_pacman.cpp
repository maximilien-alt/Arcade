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
    _level = 5;
    _score = 0;
    _beginId = 0;
    _life = 3;
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
    _ghosts.clear();
    _pacgums = 0;
    _pacgumsTotal = 0;
    _map.clear();
}

Arcade::Game_Pacman::~Game_Pacman()
{

}

void Arcade::Game_Pacman::loadMap()
{
    std::string path("ressources/pacman/maps/map_" + std::to_string(_currentMapIndex) + ".txt");
    _map = readFileIntoVector(path);
    graphical_sprite_t sprite;
    ghost_t temp;
    int spawn[2];

    temp.velocity = {0, 0, 0};
    temp.isfree = 0;
    sprite.ncursesBox = 0;
    sprite.color = {0, 0, 255, {BLUE, BLACK}};
    sprite.id = _beginId;
    sprite.path = "ressources/pacman/wall.png";
    sprite.size = {20, 20, 0};
    sprite.visible = 1;
    sprite.angle = 0;
    _start_y = HEIGHT / 2 - (_map.size() / 2) * 19;
    _start_x = WIDTH / 2 - (_map[0].length() / 2) * 9.5;
    for (size_t y = 0; y < _map.size(); y += 1) {
        for (size_t x = 0; x < _map[y].length(); x += 1) {
            sprite.pos = {float(_start_x + x * 9.5), (float)_start_y + y * 19, 0};
            sprite.id += 1;
            sprite.visible = 1;
            switch (_map[y][x]) {
                case '#':
                    sprite.path = "ressources/pacman/wall.png";
                    sprite.color = {0, 0, 255, {BLUE, BLUE}};
                    _sprites.push_back(sprite);
                    continue;
                case '.':
                    sprite.path = "ressources/pacman/coins.png";
                    sprite.color = {255, 255, 255, {WHITE, BLACK}};
                    _pacgumsTotal += 1;
                    _sprites.push_back(sprite);
                    continue;
                case '*':
                    sprite.path = "ressources/pacman/star.png";
                    sprite.color = {255, 255, 255, {WHITE, BLACK}};
                    _pacgumsTotal += 1;
                    _sprites.push_back(sprite);
                    continue;
                case 'M':
                    sprite.color = {0, 0, 0, {Arcade::COLOR(rand() % 7 + 1), BLACK}};
                    sprite.path = "ressources/pacman/ghost_up.png";
                    temp.position[0] = x;
                    temp.position[1] = y;
                    temp.sprite = sprite;
                    temp.jail[0] = x;
                    temp.jail[1] = y;
                    _ghosts.push_back(temp);
                    break;
                case 'S':
                    _pac.position[0] = x;
                    _pac.position[1] = y;
                    _pac.previousPosition[0] = x;
                    _pac.previousPosition[1] = y;
                    _pac.spwanPosition[0] = x;
                    _pac.spwanPosition[1] = y;
                    break;
                case 'G':
                    spawn[0] = x;
                    spawn[1] = y;
                    break;
                default:
                    break;
            }
            sprite.visible = 0;
            _sprites.push_back(sprite);
        }
    }
    sprite.visible = 1;
    sprite.path = "ressources/pacman/life.png";
    sprite.color = {255, 0, 0, {RED, BLACK}};
    for (int i = 0; i < _life; i += 1) {
        sprite.id += 1;
        sprite.pos = {float(WIDTH / 2 - 100 + i * 100), HEIGHT - 150, 0};
        _sprites.push_back(sprite);
    }
    sprite.id++;
    sprite.path = "ressources/pacman/pacman.png";
    sprite.angle = 180;
    _sprites.push_back(sprite);
    sprite.path = "ressources/pacman/pacman.png";
    sprite.angle = 0;
    sprite.id++;
    _sprites.push_back(sprite);
    sprite.path = "ressources/pacman/pacman.png";
    sprite.angle = 90;
    sprite.id++;
    _sprites.push_back(sprite);
    sprite.path = "ressources/pacman/pacman.png";
    sprite.angle = 270;
    sprite.id++;
    _sprites.push_back(sprite);
    _pac.velocity = {1, 0, 0};

    _box.input = _playerName;
    _box.size = {WIDTH / 10, HEIGHT / 15, 0};
    _box.pos = {WIDTH / 2, 100, 0};

    for (auto &n: _ghosts) {
        n.spwanPosition[0] = spawn[0];
        n.spwanPosition[1] = spawn[1];
    }
}

void Arcade::Game_Pacman::startGame()
{
    initValues();
    loadMap();
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
        file.close();
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

void Arcade::Game_Pacman::getPacVelocity()
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
}

void Arcade::Game_Pacman::ghostMovement(ghost_t &ghost)
{
    int proj_x = ghost.position[0] + ghost.velocity.x;
    int proj_y = ghost.position[1] + ghost.velocity.y;
    std::vector<graphical_vector_t> paths;
    int index = 0;

    if (!((size_t)proj_y < _map.size() && (size_t)proj_x < _map[0].length() && (_map[proj_y][proj_x] == '#' || _map[proj_y][proj_x] == 'x'))) {
        ghost.position[0] += ghost.velocity.x;
        ghost.position[1] += ghost.velocity.y;
        return;
    }
    //POSSIBILITIES
    proj_x = ghost.position[0] + 1;
    proj_y = ghost.position[1];
    if (!((size_t)proj_y < _map.size() && (size_t)proj_x < _map[0].length() && (_map[proj_y][proj_x] == '#' || _map[proj_y][proj_x] == 'x'))) {
        paths.push_back({1, 0, 0});
    }
    proj_x = ghost.position[0] - 1;
    proj_y = ghost.position[1];
    if (!((size_t)proj_y < _map.size() && (size_t)proj_x < _map[0].length() && (_map[proj_y][proj_x] == '#' || _map[proj_y][proj_x] == 'x'))) {
        paths.push_back({-1, 0, 0});
    }
    proj_x = ghost.position[0];
    proj_y = ghost.position[1] + 1;
    if (!((size_t)proj_y < _map.size() && (size_t)proj_x < _map[0].length() && (_map[proj_y][proj_x] == '#' || _map[proj_y][proj_x] == 'x'))) {
        paths.push_back({0, 1, 0});
    }
    proj_x = ghost.position[0];
    proj_y = ghost.position[1] - 1;
    if (!((size_t)proj_y < _map.size() && (size_t)proj_x < _map[0].length() && (_map[proj_y][proj_x] == '#' || _map[proj_y][proj_x] == 'x'))) {
        paths.push_back({0, -1, 0});
    }
    index = rand() % paths.size();
    ghost.velocity = paths[index];
    ghost.position[0] += ghost.velocity.x;
    ghost.position[1] += ghost.velocity.y;
}

void Arcade::Game_Pacman::updateGhosts()
{
    for (auto &n: _ghosts) {
        if (!n.isfree) {
            if (n.clock.getElapsedTime() > 10) {
                n.isfree = 1;
                n.position[0] = n.spwanPosition[0];
                n.position[1] = n.spwanPosition[1];
                if (rand() % 2)
                    n.velocity = {1, 0, 0};
                else
                    n.velocity = {-1, 0, 0};
                n.clock.reset();
                break;
            }
        } else {
            if (n.clock.getElapsedTime() > 1 / _level) {
                ghostMovement(n);
                n.clock.reset();
            }
        }
    }
}

void Arcade::Game_Pacman::updatePacGums()
{
    int i = _pac.position[1] * _map[0].length() + _pac.position[0];
    for (auto &n: _ghosts) {
        if (n.position[0] == _pac.position[0] && n.position[1] == _pac.position[1]) {
            if (_life == 1) {
                std::cout << "GAME OVER (implemented ?)..." << std::endl;
                exit(0);
            }
            _life -= 1;
            _sprites[_sprites.size() - (5 + _life)].visible = 0;
            for (auto &n: _ghosts) {
                n.isfree = 0;
                n.position[0] = n.jail[0];
                n.position[1] = n.jail[1];
            }
            _pac.position[0] = _pac.spwanPosition[0];
            _pac.position[1] = _pac.spwanPosition[1];
            return;
        }
    }
    if (_sprites[i].visible) {
        _sprites[i].visible = 0;
        _score += 1;
        _pacgums += 1;
        if (_pacgumsTotal == _pacgums) {
            _currentMapIndex = (_currentMapIndex == 1) ? 0 : 1;
            _level += 5;
            _beginId = _sprites.size() * _currentMapIndex;
            _sprites.clear();
            initValues();
            loadMap();
        }
    }
}

int Arcade::Game_Pacman::updateGame(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list)
{
    //UPDATE PAC MOVEMENT
    getPacVelocity();
    bool status = simulate();
    if ((_pac.velocity.y != 0 && _mainClock.getElapsedTime() > 0.13) || (_pac.velocity.x != 0 && _mainClock.getElapsedTime() > 0.09)) {
        if (status) {
            _pac.position[0] += _pac.velocity.x;
            _pac.position[1] += _pac.velocity.y;
        }
        _mainClock.reset();
        _keyPressed = 0;
    }
    updateGhosts();
    updatePacGums();
    //DRAW
    draw(_list);
    return (0);
}

void Arcade::Game_Pacman::draw(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list)
{
    graphical_vector_t goodVelocity;
    int goodIndex = 0;

    for (size_t index = 0; index < _sprites.size() - 4; index += 1)
        if (_sprites[index].visible)
            _list->push_back(std::make_pair(SPRITE, &_sprites[index]));
    for (auto &n: _ghosts) {
        n.sprite.pos.x = _start_x + n.position[0] * 9.5;
        n.sprite.pos.y = _start_y + n.position[1] * 19;
        _list->push_back(std::make_pair(SPRITE, &n.sprite));
    }
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