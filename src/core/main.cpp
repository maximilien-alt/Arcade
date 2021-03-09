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

int load_library(const char *libname, void *handle)
{
    Arcade::IGraphicalModule *(*entryPoint)(void) = NULL;

    if (!handle) {
        printf("Error on lib %s : %s\n", libname, dlerror());
        return (84);
    }
    *(void **)(&entryPoint) = dlsym(handle, "entryPoint");
    if (entryPoint == NULL) {
        std::cerr << "Unable to find entryPoint" << std::endl;
        return (84);
    }
    Arcade::IGraphicalModule *ncurses = entryPoint();
    Arcade::graphical_text_t text;
    ncurses->drawText(text);
    delete ncurses;
    dlclose(handle);
    return (0);
}

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage" << std::endl;
        return (84);
    }
    return (load_library(av[1], dlopen(av[1], RTLD_LAZY)));
}