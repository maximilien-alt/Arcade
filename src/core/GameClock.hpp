/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** GameClock
*/

#ifndef GAMECLOCK_HPP_
#define GAMECLOCK_HPP_

#include <chrono>
#include <iostream>

typedef std::chrono::high_resolution_clock Clock;

namespace Arcade
{
    class GameClock
    {
    public:
        GameClock();
        ~GameClock();
        void reset();
        float getElapsedTime();

    private:
        std::chrono::_V2::system_clock::time_point _clock = Clock::now();

    };
}

#endif /* !GAMECLOCK_HPP_ */
