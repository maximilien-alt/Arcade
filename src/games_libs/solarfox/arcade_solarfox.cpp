/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** arcade_solarfox
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "arcade_solarfox.hpp"

Arcade::Game_Solarfox::Game_Solarfox() : AGameModule()
{
}

Arcade::Game_Solarfox::~Game_Solarfox()
{
}

int Arcade::Game_Solarfox::distanceBetween(graphical_vector_t pos1, graphical_vector_t pos2)
{
    return sqrt(pow(pos2.x - pos1.x, 2) + pow(pos2.y - pos1.y, 2));
}

void Arcade::Game_Solarfox::createEnnemies()
{
    graphical_sprite_t sprite;
    sprite.id = 0;
    sprite.visible = 1;
    sprite.path = "ressources/solarfox/solarfox_ennemy.png";
    sprite.color = {255, 0, 0, {RED, BLACK}};
    sprite.pos = {_box.pos.x - _box.size.x / 2 + 120, _box.pos.y - _box.size.y / 2 + 8, 0};
    sprite.size = {36, 18, 0};
    sprite.angle = 180;
    sprite.ncursesBox = 0;
    _sprites.push_back(sprite);

    sprite.id++;
    sprite.path = "ressources/solarfox/solarfox_ennemy.png";
    sprite.pos = {_box.pos.x + _box.size.x / 2 - 10, _box.pos.y - _box.size.y / 2 + 120, 0};
    sprite.angle = 270;
    _sprites.push_back(sprite);

    sprite.id++;
    sprite.path = "ressources/solarfox/solarfox_ennemy.png";
    sprite.pos = {(_box.pos.x + _box.size.x / 2 - 120), (_box.pos.y + _box.size.y / 2 - 8), 0};
    sprite.angle = 0;
    _sprites.push_back(sprite);

    sprite.id++;
    sprite.path = "ressources/solarfox/solarfox_ennemy.png";
    sprite.angle = 90;
    sprite.pos = {(_box.pos.x - _box.size.x / 2 + 8), (_box.pos.y + _box.size.y / 2 - 120), 0};
    _sprites.push_back(sprite);

    _spriteIndex = 3;
    GameClock clock;
    _ennemiesClocks.push_back(clock);
    _ennemiesClocks.push_back(clock);
    _ennemiesClocks.push_back(clock);
    _ennemiesClocks.push_back(clock);
}

void Arcade::Game_Solarfox::createPlayer()
{
    graphical_sprite_t player;
    player.id = 4;
    player.visible = 1;
    player.path = "ressources/solarfox/solarfox_player.png";
    player.color = {255, 0, 0, {WHITE, BLACK}};
    player.pos = {(_box.pos.x + _box.size.x / 4), (_box.pos.y + _box.size.y / 4 - 120), 0};
    player.size = {36, 18, 0};
    player.angle = 0;
    player.ncursesBox = 0;
    _sprites.push_back(player);

    graphical_sprite_t shot;
    shot.id = 5;
    shot.path = "ressources/solarfox/solarfox_shot.png";
    shot.color = {255, 0, 0, {WHITE, BLACK}};
    shot.pos = {0, 0, 0};
    shot.angle = 0;
    shot.ncursesBox = 0;
    shot.visible = 0;
    _sprites.push_back(shot);

    _spriteIndex = 5;
}

void Arcade::Game_Solarfox::startGame()
{
    _box.pos = {WIDTH / 2, HEIGHT / 2, 0};
    _box.size = {40 * 15, 40 * 15, 0};

    createEnnemies();
    createPlayer();

    _ennemiesDirection[0] = 1;
    _ennemiesDirection[1] = 1;
    _ennemiesDirection[2] = -1;
    _ennemiesDirection[3] = -1;
}

void Arcade::Game_Solarfox::calcEnnemiesPositions()
{
    _sprites[0].pos.x += _ennemiesDirection[0];
    if (_sprites[0].pos.x >= _box.pos.x - _box.size.x / 2 + _box.size.x - 16)
    {
        _ennemiesDirection[0] = -0.7;
    }
    else if (_sprites[0].pos.x <= _box.pos.x - _box.size.x / 2 + 16)
        _ennemiesDirection[0] = 0.7;

    _sprites[1].pos.y += _ennemiesDirection[1];
    if (_sprites[1].pos.y >= _box.pos.y - _box.size.y / 2 + _box.size.y - 16)
    {
        _ennemiesDirection[1] = -1;
    }
    else if (_sprites[1].pos.y <= _box.pos.y - _box.size.y / 2 + 16)
        _ennemiesDirection[1] = 1;

    _sprites[2].pos.x += _ennemiesDirection[2];
    if (_sprites[2].pos.x >= _box.pos.x - _box.size.x / 2 + _box.size.x - 16)
    {
        _ennemiesDirection[2] = -0.5;
    }
    else if (_sprites[2].pos.x <= _box.pos.x - _box.size.x / 2 + 16)
        _ennemiesDirection[2] = 0.5;

    _sprites[3].pos.y += _ennemiesDirection[3];
    if (_sprites[3].pos.y >= _box.pos.y - _box.size.y / 2 + _box.size.y - 16)
    {
        _ennemiesDirection[3] = -0.8;
    }
    else if (_sprites[3].pos.y <= _box.pos.y - _box.size.y / 2 + 16)
        _ennemiesDirection[3] = 0.8;
}

void Arcade::Game_Solarfox::calcPlayerPosition()
{
    if (_sprites[4].angle == 0)
    {
        if (_sprites[4].pos.y > _box.pos.y - _box.size.y / 2 + 10)
            _sprites[4].pos.y -= 1;
        else
            endGame();
    }
    else if (_sprites[4].angle == 90)
    {
        if (_sprites[4].pos.x < _box.pos.x - _box.size.x / 2 + _box.size.x - 10)
            _sprites[4].pos.x += 1;
        else
            endGame();
    }
    else if (_sprites[4].angle == 180)
    {
        if (_sprites[4].pos.y < _box.pos.y - _box.size.y / 2 + _box.size.y - 10)
            _sprites[4].pos.y += 1;
        else
            endGame();
    }
    else if (_sprites[4].angle == 270)
    {
        if (_sprites[4].pos.x > _box.pos.x - _box.size.x / 2 + 10)
            _sprites[4].pos.x -= 1;
        else
            endGame();
    }
    if (!_sprites[5].visible)
        return;
    if (_sprites[5].angle == 0)
        _sprites[5].pos.y -= 2.5;
    if (_sprites[5].angle == 90)
        _sprites[5].pos.x += 2.5;
    if (_sprites[5].angle == 180)
        _sprites[5].pos.y += 2.5;
    if (_sprites[5].angle == 270)
        _sprites[5].pos.x -= 2.5;
}

void Arcade::Game_Solarfox::ennemyShot(graphical_sprite_t &ennemy, GameClock &clock)
{
    if (clock.getElapsedTime() > 2)
    {
        clock.reset();
        const int distance = distanceBetween(ennemy.pos, _sprites[4].pos);
        if (distance < 350)
        {
            _spriteIndex++;
            graphical_sprite_t shot;
            shot.id = _spriteIndex;
            shot.visible = 1;
            shot.path = "ressources/solarfox/solarfox_rocket.png";
            shot.color = {255, 0, 0, {RED, BLACK}};
            shot.pos = {ennemy.pos.x, ennemy.pos.y, 0};
            shot.size = {36, 18, 0};
            shot.angle = ennemy.angle;
            shot.ncursesBox = 0;
            _ennemiesShots.push_back(shot);
        }
    }
}

void Arcade::Game_Solarfox::playerShot()
{
    if (_sprites[5].visible)
        return;
    _sprites[5].pos = _sprites[4].pos;
    _sprites[5].angle = _sprites[4].angle;
    _sprites[5].visible = 1;
    _shotClock.reset();
}

void Arcade::Game_Solarfox::calcEnnemiesShots()
{
    for (size_t i = 0; i < _ennemiesShots.size(); i++)
    {
        if (distanceBetween(_ennemiesShots[i].pos, _sprites[4].pos) < 20) {
            endGame();
        }
        if (distanceBetween(_ennemiesShots[i].pos, _sprites[5].pos) < 20) {
            _ennemiesShots.erase(_ennemiesShots.begin() + i);
            continue;
        }
        if (_ennemiesShots[i].angle == 0)
        {
            if (_ennemiesShots[i].pos.y > _box.pos.y - _box.size.y / 2 + 60)
                _ennemiesShots[i].pos.y -= 1;
            else
                _ennemiesShots.erase(_ennemiesShots.begin() + i);
        }
        else if (_ennemiesShots[i].angle == 90)
        {
            if (_ennemiesShots[i].pos.x < _box.pos.x - _box.size.x / 2 + _box.size.x - 60)
                _ennemiesShots[i].pos.x += 1;
            else
                _ennemiesShots.erase(_ennemiesShots.begin() + i);
        }
        else if (_ennemiesShots[i].angle == 180)
        {
            if (_ennemiesShots[i].pos.y < _box.pos.y - _box.size.y / 2 + _box.size.y - 60)
                _ennemiesShots[i].pos.y += 1;
            else
                _ennemiesShots.erase(_ennemiesShots.begin() + i);
        }
        else if (_ennemiesShots[i].angle == 270)
        {
            if (_ennemiesShots[i].pos.x > _box.pos.x - _box.size.x / 2 + 60)
                _ennemiesShots[i].pos.x -= 1;
            else
                _ennemiesShots.erase(_ennemiesShots.begin() + i);
        }
    }
}

void Arcade::Game_Solarfox::endGame()
{
    std::cout << "RIP" << std::endl;
    exit(0);
}

void Arcade::Game_Solarfox::handleKeys()
{
    if (_keys[ARROW_UP] && _sprites[4].angle != 180)
    {
        _playerDirection = 0;
        _sprites[4].angle = 0;
    }
    else if (_keys[ARROW_RIGHT] && _sprites[4].angle != 270)
    {
        _sprites[4].angle = 90;
    }
    else if (_keys[ARROW_DOWN] && _sprites[4].angle != 0)
    {
        _sprites[4].angle = 180;
    }
    else if (_keys[ARROW_LEFT] && _playerDirection != 90)
    {
        _sprites[4].angle = 270;
    } else if (_keys[SPACE]) {
        playerShot();
    }
}

int Arcade::Game_Solarfox::updateGame(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *list)
{
    handleKeys();
    if (_shotClock.getElapsedTime() > 0.3)
        _sprites[5].visible = 0;
    if (_mainClock.getElapsedTime() > 0.005)
    {
        _mainClock.reset();
        calcEnnemiesPositions();
        calcPlayerPosition();
        calcEnnemiesShots();
        for (size_t i = 0; i < 4; i++)
            ennemyShot(_sprites[i], _ennemiesClocks[i]);
    }
    draw(list);
    return (0);
}

void Arcade::Game_Solarfox::draw(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *list)
{
    list->push_back(std::make_pair(BOX, &_box));
    for (auto &n : _texts)
        list->push_back(std::make_pair(TEXT, &n));
    for (auto &n : _sprites)
        list->push_back(std::make_pair(SPRITE, &n));
    for (auto &n : _ennemiesShots)
        list->push_back(std::make_pair(SPRITE, &n));
}

extern "C" Arcade::IGameModule *entryPoint(void)
{
    return new Arcade::Game_Solarfox;
}