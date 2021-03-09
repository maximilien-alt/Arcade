/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** LDL
*/

#include "LDL.hpp"

void *Arcade::LDL::open(const char *path)
{
    return (dlopen(path, RTLD_LAZY));
}

char *Arcade::LDL::error()
{
    return (dlerror());
}

void *Arcade::LDL::sym(void *handle, const char *symbol)
{
    return (dlsym(handle, symbol));
}

int Arcade::LDL::close(void *handle)
{
    return (dlclose(handle));
}