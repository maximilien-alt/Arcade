/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** GameClock
*/

#include "GameClock.hpp"

Arcade::GameClock::GameClock()
{
}

Arcade::GameClock::~GameClock()
{
}

void Arcade::GameClock::reset()
{
    _clock = Clock::now();
}

float Arcade::GameClock::getElapsedTime()
{
    auto now = Clock::now();
    float elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(now - _clock).count();

    return (elapsedTime / 1000000);
}