/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** AGRAPHICAL_MODULE
*/

#ifndef AGRAPHICAL_MODULE_HPP_
#define AGRAPHICAL_MODULE_HPP_

#include "IGraphicalModule.hpp"

namespace Arcade
{
    class AGraphicalModule : public IGraphicalModule
    {
    public:
        AGraphicalModule();
        virtual ~AGraphicalModule() = default;

        virtual void drawText(graphical_text_t &text) = 0;
    };
}

#endif /* !AGRAPHICAL_MODULE_HPP_ */
