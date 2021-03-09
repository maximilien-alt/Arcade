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
#include "LibraryManager.hpp"

int load_library(const char *libname, void *handle)
{
    Arcade::IGraphicalModule *(*entryPoint)(void) = NULL;

    if (!handle) {
        printf("Unable to load library %s : %s\n", libname, dlerror());
        return (84);
    }
    *(void **)(&entryPoint) = dlsym(handle, "entryPoint");
    if (entryPoint == NULL) {
        std::cerr << "Unable to find entryPoint" << std::endl;
        return (84);
    }
    Arcade::IGraphicalModule *graphicalModule = entryPoint();
    Arcade::LibraryManager libraryManager(graphicalModule);
    libraryManager.openMenu();
    delete graphicalModule;
    dlclose(handle);
    return (0);
}

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: ./arcade Graphical_Library.so" << std::endl;
        return (84);
    }
    return (load_library(av[1], dlopen(av[1], RTLD_LAZY)));
}