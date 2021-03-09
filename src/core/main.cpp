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


void load_library(const char *libname, void *handle)
{
    int (*entryPoint)(void) = NULL;

    if (!handle) {
        printf("Error on lib %s", libname);
        return;
    }
    *(void **)(&entryPoint) = dlsym(handle, "entryPoint");
    entryPoint();
    dlclose(handle);
}

int main(int ac, char **av)
{
    void *handle = NULL;

    for (int i = 1; i < ac; i++) {
        handle = dlopen(av[i], RTLD_LAZY);
        load_library(av[i], handle);
    }
}