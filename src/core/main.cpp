/*
** EPITECH PROJECT, 2021
** bootstrap_arcade
** File description:
** main
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include "IGraphicalModule.hpp"
#include "Simulator.hpp"

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: ./arcade Graphical_Library.so" << std::endl;
        return (84);
    }
    try {
        const std::string path = av[1];
        Arcade::Simulator simulator(path);
        simulator.run();
    } catch (Arcade::Errors &error) {
        std::cerr << error.what() << std::endl;
        return (84);
    }
    return (0);
}