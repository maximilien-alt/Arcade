/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** LDL
*/

#ifndef LDL_HPP_
#define LDL_HPP_

#include <dlfcn.h>

namespace Arcade
{
    class LDL {
        public:
            static void *open(const char *path);
            static char *error();
            static void *sym(void *handle, const char *symbol);
            static int close(void *handle);
        protected:
        private:
    };
}

#endif /* !LDL_HPP_ */
