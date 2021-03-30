/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** Tools
*/

#include "Tools.hpp"

std::vector<std::string> Arcade::Tools::readFileIntoVector(std::string filepath)
{
    std::vector<std::string> res;
    std::ifstream file(filepath);
    std::string temp;

    if (file.is_open()) {
        while (std::getline(file, temp)) {
            res.push_back(temp);
        }
    }
    return (res);
}
