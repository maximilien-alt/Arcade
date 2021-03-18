/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** Tools
*/

#ifndef TOOLS_HPP_
#define TOOLS_HPP_

#include <iostream>
#include <vector>
#include <fstream>

namespace Arcade {

class Tools {
        public:
            static std::vector<std::string> readFileIntoVector(std::string filepath);
    };
}
#endif