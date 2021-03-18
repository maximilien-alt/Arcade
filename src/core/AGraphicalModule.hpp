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
        virtual void drawSprite(graphical_sprite_t &sprite) = 0;
        virtual void reset() = 0;
        virtual void showInputBox(graphical_box_t &box) = 0;
        virtual void clear() = 0;
        virtual void refresh() = 0;
        virtual void updateInputsMap() = 0;
        virtual void openWindow() = 0;
        virtual void closeWindow() = 0;

        std::unordered_map<int, bool> getInputsMap() const final;
        void resetKeys() final;
    
    protected:
        std::unordered_map<int, bool> _keys;
    };
}

#endif /* !AGRAPHICAL_MODULE_HPP_ */
