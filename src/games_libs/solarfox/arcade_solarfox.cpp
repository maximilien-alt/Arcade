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

Arcade::Game_Solarfox::Game_Solarfox(): AGameModule()
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
    sprite.path = "ressources/solarfox/solarfox_ennemy_up.png";
    sprite.color = {255, 0, 0, {RED, BLACK}};
    sprite.pos = {_box.pos.x - _box.size.x / 2 + 120, _box.pos.y - _box.size.y / 2 + 8, 0};
    sprite.size = {36, 18, 0};
    sprite.ncursesBox = 0;
    _sprites.push_back(sprite);

    sprite.id++;
    sprite.path = "ressources/solarfox/solarfox_ennemy_right.png";
    sprite.pos = {_box.pos.x + _box.size.x / 2 - 10, _box.pos.y - _box.size.y / 2 + 120, 0};
    _sprites.push_back(sprite);

    sprite.id++;
    sprite.path = "ressources/solarfox/solarfox_ennemy.png";
    sprite.pos = {(_box.pos.x + _box.size.x / 2 - 120), (_box.pos.y + _box.size.y / 2 - 8), 0};
    _sprites.push_back(sprite);

    sprite.id++;
    sprite.path = "ressources/solarfox/solarfox_ennemy_left.png";
    sprite.pos = {(_box.pos.x - _box.size.x / 2 + 8), (_box.pos.y + _box.size.y / 2 - 120), 0};
    _sprites.push_back(sprite);

    GameClock clock;
    _ennemiesClocks.push_back(clock);
    _ennemiesClocks.push_back(clock);
    _ennemiesClocks.push_back(clock);
    _ennemiesClocks.push_back(clock);
}

void Arcade::Game_Solarfox::createPlayer()
{
    _playerPosition = {(_box.pos.x + _box.size.x / 4), (_box.pos.y + _box.size.y / 4 - 120), 0};

    graphical_sprite_t player;
    player.id = 4;
    player.path = "ressources/solarfox/solarfox_player.png";
    player.color = {255, 0, 0, {WHITE, BLACK}};
    player.pos = _playerPosition;
    player.size = {36, 18, 0};
    player.ncursesBox = 0;
    _sprites.push_back(player);

    player.id++;
    player.path = "ressources/solarfox/solarfox_player_left.png";
    _sprites.push_back(player);

    player.id++;
    player.path = "ressources/solarfox/solarfox_player_up.png";
    _sprites.push_back(player);

    player.id++;
    player.path = "ressources/solarfox/solarfox_player_right.png";
    _sprites.push_back(player);
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
    if (_sprites[0].pos.x >= _box.pos.x - _box.size.x / 2 + _box.size.x - 16) {
        _ennemiesDirection[0] = -0.7;
    } else if (_sprites[0].pos.x <= _box.pos.x - _box.size.x / 2 + 16)
        _ennemiesDirection[0] = 0.7;

    _sprites[1].pos.y += _ennemiesDirection[1];
    if (_sprites[1].pos.y >= _box.pos.y - _box.size.y / 2 + _box.size.y - 16) {
        _ennemiesDirection[1] = -1;
    } else if (_sprites[1].pos.y <= _box.pos.y - _box.size.y / 2 + 16)
        _ennemiesDirection[1] = 1;

    _sprites[2].pos.x += _ennemiesDirection[2];
    if (_sprites[2].pos.x >= _box.pos.x - _box.size.x / 2 + _box.size.x - 16) {
        _ennemiesDirection[2] = -0.5;
    } else if (_sprites[2].pos.x <= _box.pos.x - _box.size.x / 2 + 16)
        _ennemiesDirection[2] = 0.5;

    _sprites[3].pos.y += _ennemiesDirection[3];
    if (_sprites[3].pos.y >= _box.pos.y - _box.size.y / 2 + _box.size.y - 16) {
        _ennemiesDirection[3] = -0.8;
    } else if (_sprites[3].pos.y <= _box.pos.y - _box.size.y / 2 + 16)
        _ennemiesDirection[3] = 0.8;
}

void Arcade::Game_Solarfox::calcPlayerPosition()
{
    switch (_playerDirection) {
        case 0:
            if (_playerPosition.y > _box.pos.y - _box.size.y / 2 + 60)
                _playerPosition.y -= 1;
            break;
        case 1:
            if (_playerPosition.x < _box.pos.x - _box.size.x / 2 + _box.size.x - 60)
                _playerPosition.x += 1;
            break;
        case 2:
            if (_playerPosition.y < _box.pos.y - _box.size.y / 2 + _box.size.y - 60)
                _playerPosition.y += 1;
            break;
        case 3:
            if (_playerPosition.x > _box.pos.x - _box.size.x / 2 + 60)
                _playerPosition.x -= 1;
            break;
    }
}

void Arcade::Game_Solarfox::ennemyShot(graphical_sprite_t sprite, GameClock clock)
{
    if (clock.getElapsedTime() > 2) {
        const int distance = distanceBetween(sprite.pos, _sprites[_playerDirection + 4].pos);
        if (distance < 200) {
            // shot
        }
    }
}

void Arcade::Game_Solarfox::handleKeys()
{
    if (_keys[ARROW_UP] && _playerDirection != 2) {
        _playerDirection = 0;
    } else if (_keys[ARROW_RIGHT] && _playerDirection != 3) {
        _playerDirection = 1;
    } else if (_keys[ARROW_DOWN] && _playerDirection != 0) {
        _playerDirection = 2;
    } else if (_keys[ARROW_LEFT] && _playerDirection != 1) {
        _playerDirection = 3;
    }
}

int Arcade::Game_Solarfox::updateGame(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *list)
{
    handleKeys();
    if (_mainClock.getElapsedTime() > 0.005) {
        _mainClock.reset();
        calcEnnemiesPositions();
        calcPlayerPosition();
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
    for (auto &n : _sprites) {
        if (n.id - 4 == _playerDirection)
            n.pos = _playerPosition;
        if ((n.id < 4 || n.id > 7) || (n.id - 4 == _playerDirection))
            list->push_back(std::make_pair(SPRITE, &n));
    }
}

extern "C" Arcade::IGameModule *entryPoint(void)
{
    return new Arcade::Game_Solarfox;
}