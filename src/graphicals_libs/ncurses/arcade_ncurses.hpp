/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** arcade_ncurses
*/

#ifndef ARCADE_NCURSES_HPP_
#define ARCADE_NCURSES_HPP_

#include "../../core/AGraphicalModule.hpp"
#include <iostream>
#include <fstream>

namespace Arcade
{
    class Graphical_Ncurses : public AGraphicalModule {
        public:
            Graphical_Ncurses();
            ~Graphical_Ncurses();
            void drawText(graphical_text_t &text) final;
            void drawSprite(graphical_sprite_t &sprite) final;
            void showInputBox(graphical_box_t &box) final;
            void reset() final;
            void clear() final;
            void refresh() final;
            void updateInputsMap() final;
            void openWindow() final;
            void closeWindow() final;

        private:
            std::vector<WINDOW *> _windows;
            int colors[2][2][2];
            std::ofstream stream;
            std::unordered_map<int, std::pair<std::vector<std::string>, WINDOW *>> _sprites;
            bool showBox = false;

            int getInput();
            int getPair(Arcade::graphical_color_t color) const;
            void init_colors_pairs();
            std::vector<std::string> readFileIntoVector(std::string filepath);
            WINDOW *init_new_window(int a, int b, int c, int d);

    };
} // namespace Arcade

#endif /* !ARCADE_NCURSES_HPP_ */
