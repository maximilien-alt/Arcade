/*
** EPITECH PROJECT, 2021
** bootstrap_arcade
** File description:
** lib1
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

__attribute__((constructor))
void constructor()
{
    printf("[libfoo] Loading foo library...\n");
}

__attribute__((destructor))
void destructor()
{
    printf("[libfoo] foo closing...\n");
}

extern "C" int entryPoint(void)
{
    printf("[libfoo] Entry point for foo!\n");
    return (0);
}