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
    std::chrono::duration<double, std::micro> elapsedTime = now - _clock;

    return (elapsedTime.count() / 1000000);
}