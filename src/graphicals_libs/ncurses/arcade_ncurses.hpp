/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** arcade_ncurses
*/

#ifndef ARCADE_NCURSES_HPP_
#define ARCADE_NCURSES_HPP_

#include "../../core/AGraphicalModule.hpp"

namespace Arcade
{
    class Graphical_Ncurses : public AGraphicalModule {
        public:
            Graphical_Ncurses();
            ~Graphical_Ncurses();
            void drawText(graphical_text_t &text) final;
            void clear() final;
            void refresh() final;
        
        private:
            WINDOW *_win;
    };
} // namespace Arcade

#endif /* !ARCADE_NCURSES_HPP_ */