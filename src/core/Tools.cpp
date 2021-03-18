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
    std::ofstream stream("debug.txt", std::ios::app);

    stream << "yyoyoyoyo" << std::endl;
    if (file.is_open()) {
        stream << "yo" << std::endl;
        while (std::getline(file, temp)) {
            stream << temp << std::endl;
            res.push_back(temp);
        }
    } else {
        stream << "can't" << std::endl;
    }
    return (res);
}
