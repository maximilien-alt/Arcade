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
    _lifeMax = 3;
    _life = _lifeMax;
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
                    temp.position[0] = x;
                    temp.position[1] = y;
                    temp.previousPosition[0] = x;
                    temp.previousPosition[1] = y;
                    temp.jail[0] = x;
                    temp.jail[1] = y;
                    temp.fIterations = 0;
                    temp.isDead = 0;
                    temp.isfree = 0;
                    temp.isFreeze = 0;
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
    //sprite.visible = 0;
    for (auto &n: _ghosts) {
        sprite.color = {0, 0, 0, {Arcade::COLOR(rand() % 7 + 1), BLACK}};
        sprite.id += 1;
        sprite.path = "ressources/pacman/ghost_up.png";
        n.sprites.push_back(sprite);
        sprite.id += 1;
        sprite.path = "ressources/pacman/ghost_right.png";
        n.sprites.push_back(sprite);
        sprite.id += 1;
        sprite.path = "ressources/pacman/ghost_down.png";
        n.sprites.push_back(sprite);
        sprite.id += 1;
        sprite.path = "ressources/pacman/ghost_left.png";
        n.sprites.push_back(sprite);
        sprite.id += 1;
        sprite.color = {0, 0, 255, {BLUE, CYAN}};
        sprite.path = "ressources/pacman/ghost_mad.png";
        n.sprites.push_back(sprite);
        sprite.id += 1;
        sprite.color = {0, 0, 255, {RED, MAGENTA}};
        sprite.path = "ressources/pacman/ghost_eye.png";
        n.sprites.push_back(sprite);
        n.spwanPosition[0] = spawn[0];
        n.spwanPosition[1] = spawn[1];
    }
    sprite.visible = 1;
    sprite.path = "ressources/pacman/life.png";
    sprite.color = {255, 0, 0, {RED, BLACK}};
    for (int i = 0; i < _lifeMax; i += 1) {
        sprite.visible = (i < _life);
        sprite.id += 1;
        sprite.pos = {float(WIDTH / 2 - 100 + i * 100), HEIGHT - 150, 0};
        _sprites.push_back(sprite);
    }
    sprite.visible = 1;
    sprite.id++;
    sprite.path = "ressources/pacman/pacman.png";
    sprite.angle = 0;
    _sprites.push_back(sprite);
    _pac.velocity = {1, 0, 0};

    _box.input = _playerName;
    _box.size = {WIDTH / 10, HEIGHT / 15, 0};
    _box.pos = {WIDTH / 2, 100, 0};
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

void Arcade::Game_Pacman::followPath(ghost_t &ghost)
{
    int proj_x = ghost.position[0] + 1;
    int proj_y = ghost.position[1];
    if (!((size_t)proj_y < ghost.path.size() && (size_t)proj_x < ghost.path[0].length() && ghost.path[proj_y][proj_x] != 'o')) {
        ghost.velocity = {1, 0, 0};
        ghost.path[proj_y][proj_x] = ' ';
    }
    proj_x = ghost.position[0] - 1;
    proj_y = ghost.position[1];
    if (!((size_t)proj_y < ghost.path.size() && (size_t)proj_x < ghost.path[0].length() && ghost.path[proj_y][proj_x] != 'o')) {
        ghost.velocity = {-1, 0, 0};
        ghost.path[proj_y][proj_x] = ' ';
    }
    proj_x = ghost.position[0];
    proj_y = ghost.position[1] + 1;
    if (!((size_t)proj_y < ghost.path.size() && (size_t)proj_x < ghost.path[0].length() && ghost.path[proj_y][proj_x] != 'o')) {
        ghost.velocity = {0, 1, 0};
        ghost.path[proj_y][proj_x] = ' ';
    }
    proj_x = ghost.position[0];
    proj_y = ghost.position[1] - 1;
    if (!((size_t)proj_y < ghost.path.size() && (size_t)proj_x < ghost.path[0].length() && ghost.path[proj_y][proj_x] != 'o')) {
        ghost.velocity = {0, -1, 0};
        ghost.path[proj_y][proj_x] = ' ';
    }
    ghost.path[ghost.position[1]][ghost.position[0]] = ' ';
    ghost.position[0] += ghost.velocity.x;
    ghost.position[1] += ghost.velocity.y;
}

void Arcade::Game_Pacman::ghostMovement(ghost_t &ghost)
{
    if (ghost.path.size() > 0)
        return followPath(ghost);
    std::vector<graphical_vector_t> paths;
    //POSSIBILITIES
    int proj_x = ghost.position[0] + 1;
    int proj_y = ghost.position[1];
    if (!((size_t)proj_y < _map.size() && (size_t)proj_x < _map[0].length() && (_map[proj_y][proj_x] == '#' || _map[proj_y][proj_x] == 'x'))) {
        if (ghost.velocity.x != -1)
            paths.push_back({1, 0, 0});
    }
    proj_x = ghost.position[0] - 1;
    proj_y = ghost.position[1];
    if (!((size_t)proj_y < _map.size() && (size_t)proj_x < _map[0].length() && (_map[proj_y][proj_x] == '#' || _map[proj_y][proj_x] == 'x'))) {
        if (ghost.velocity.x != 1)
            paths.push_back({-1, 0, 0});
    }
    proj_x = ghost.position[0];
    proj_y = ghost.position[1] + 1;
    if (!((size_t)proj_y < _map.size() && (size_t)proj_x < _map[0].length() && (_map[proj_y][proj_x] == '#' || _map[proj_y][proj_x] == 'x'))) {
        if (ghost.velocity.y != -1)
            paths.push_back({0, 1, 0});
    }
    proj_x = ghost.position[0];
    proj_y = ghost.position[1] - 1;
    if (!((size_t)proj_y < _map.size() && (size_t)proj_x < _map[0].length() && (_map[proj_y][proj_x] == '#' || _map[proj_y][proj_x] == 'x'))) {
        if (ghost.velocity.y != 1)
            paths.push_back({0, -1, 0});
    }
    int index = rand() % paths.size();
    ghost.velocity = paths[index];
    ghost.position[0] += ghost.velocity.x;
    ghost.position[1] += ghost.velocity.y;
}

void Arcade::Game_Pacman::updateGhosts()
{
    float cl = 0;

    if (_ghosts[0].isfree && !_ghosts[0].isFreeze && !_ghosts[0].isDead) {
        _ghosts[0].path = star.findWay(_map, std::make_pair(_ghosts[0].position[0], _ghosts[0].position[1]), std::make_pair(_pac.position[0], _pac.position[1]));
    }
    for (auto &n: _ghosts) {
        n.previousPosition[0] = n.position[0];
        n.previousPosition[1] = n.position[1];
        if (n.isDead) {
            cl = n.eaten.getElapsedTime();
            if (cl > 0.06) {
                ghostMovement(n);
                n.eaten.reset();
                if (n.position[0] == n.spwanPosition[0] && n.position[1] == n.spwanPosition[1]) {
                    n.isfree = 0;
                    n.isDead = 0;
                    n.position[0] = n.jail[0];
                    n.position[1] = n.jail[1];
                    n.path.clear();
                }
            }
            continue;
        }
        cl = n.clock.getElapsedTime();
        if (n.isFreeze) {
            n.path.clear();
            if (cl > 0.5) {
                n.fIterations += 1;
                ghostMovement(n);
                if (n.fIterations == 10) {
                    n.fIterations = 0;
                    n.isFreeze = 0;
                }
                n.clock.reset();
            }
        } else {
            if (!n.isfree) {
                if (cl > 10) {
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
                if (cl > 1 / _level) {
                    ghostMovement(n);
                    n.clock.reset();
                }
            }
        }
    }
}

void Arcade::Game_Pacman::updatePacGums()
{
    int i = _pac.position[1] * _map[0].length() + _pac.position[0];

    for (auto &n: _ghosts) {
        if (n.position[0] == _pac.position[0] && n.position[1] == _pac.position[1]) {
            //GHOST COLLISION
            if (n.isFreeze && !n.isDead) {
                n.path = star.findWay(_map, std::make_pair(n.position[0], n.position[1]), std::make_pair(n.spwanPosition[0], n.spwanPosition[1]));
                n.isFreeze = 0;
                n.fIterations = 0;
                n.isDead = 1;
            } else if (!n.isDead) {
                if (_life == 1) {
                    std::cout << "GAME OVER (implemented ?)..." << std::endl;
                    exit(0);
                }
                _life -= 1;
                _sprites[_sprites.size() - (2 + _life)].visible = 0;
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
    }
    if (_sprites[i].visible) {
        //DELETING PACGUM
        _sprites[i].visible = 0;
        _score += 1;
        _pacgums += 1;
        //CHAGING LEVEL
        if (_pacgumsTotal == _pacgums) {
            _currentMapIndex = (_currentMapIndex == 1) ? 0 : 1;
            _level += 5;
            _beginId = (_sprites.size() + _ghosts.size() * 5) * _currentMapIndex;
            _sprites.clear();
            initValues();
            return (loadMap());
        }
        //FREEZING GHOSTS
        if (_map[_pac.position[1]][_pac.position[0]] == '*') {
            for (auto &n: _ghosts) {
                if (n.isfree && !n.isDead)
                    n.isFreeze = 1;
            }
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
            if ((size_t)_pac.position[0] >= _map[0].length())
                _pac.position[0] = 0;
            if (_pac.position[0] <= 0)
                _pac.position[0] = _map[0].length() - 1;
            if ((size_t)_pac.position[1] >= _map.size())
                _pac.position[1] = 0;
            if (_pac.position[1] <= 0)
                _pac.position[1] = _map.size() - 1;
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

void Arcade::Game_Pacman::smoothDraw(int prev[2], int now[2], graphical_sprite_t &sprite, GameClock clock)
{
    float start_y = _start_y + prev[1] * 19;
    float start_x = _start_x + prev[0] * 9.5;
    float end_y = _start_y + now[1] * 19;
    float end_x = _start_x + now[0] * 9.5;

    sprite.pos.y = start_y;
    sprite.pos.x = start_x;
    //std::cout << "start_y: "<< start_y << "start_x: "<< start_x << "end_y: "<< end_y << "end_x: "<< end_x<< std::endl;
    if (prev[0] == now[0] && prev[1] == now[1])
        return;
    if (prev[1] == now[1]) {
        if (clock.getElapsedTime() > 0.00002) {
            clock.reset();
            sprite.pos.x = (start_x > end_x) ? sprite.pos.x - 2.375: sprite.pos.x + 2.375;
        }
    } else {
        if (clock.getElapsedTime() > 0.00002) {
            clock.reset();
            sprite.pos.y = (start_y > end_y) ? sprite.pos.y - 4.75: sprite.pos.y + 4.75;
        }
    }
}

void Arcade::Game_Pacman::draw(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *_list)
{
    graphical_vector_t goodVelocity;
    int goodIndex = 0;

    for (size_t index = 0; index < _sprites.size() - 1; index += 1)
        if (_sprites[index].visible)
            _list->push_back(std::make_pair(SPRITE, &_sprites[index]));
    for (auto &n: _ghosts) {
        if (n.velocity.x == 1)
            goodIndex = 1;
        else if (n.velocity.x == -1)
            goodIndex = 3;
        else if (n.velocity.y == 1)
            goodIndex = 2;
        else
            goodIndex = 0;
        goodIndex = (n.isFreeze) ? 4 : goodIndex;
        if (n.isDead)
            goodIndex = 5;
        //n.sprites[goodIndex].pos.x = _start_x + n.position[0] * 9.5;
        //n.sprites[goodIndex].pos.y = _start_y + n.position[1] * 19;
        smoothDraw(n.previousPosition, n.position, n.sprites[goodIndex], n.draw);
        _list->push_back(std::make_pair(SPRITE, &n.sprites[goodIndex]));
    }
    goodVelocity = ((_pac.velocity.x != 0 || _pac.velocity.y != 0) && !_keyPressed) ? _pac.velocity : _pac.previousVelocity;
    graphical_sprite_t &sprite = _sprites[_sprites.size() - 1];

    if (goodVelocity.x == 1) {
       sprite.angle = 270;
    } else if (goodVelocity.x == -1) {
       sprite.angle = 90;
    } else if (goodVelocity.y == 1)
       sprite.angle = 0;
    else
       sprite.angle = 180;
    //sprite.pos.x = _start_x + _pac.position[0] * 9.5;
    //sprite.pos.y = _start_y + _pac.position[1] * 19;
    smoothDraw(_pac.previousPosition, _pac.position, sprite, _pac.draw);
    _list->push_back(std::make_pair(SPRITE, &sprite));
    _box.input = _playerName + " " + std::to_string(_score);
    _list->push_back(std::make_pair(BOX, &_box));
}

extern "C" Arcade::IGameModule *entryPoint(void)
{
    return new Arcade::Game_Pacman;
}