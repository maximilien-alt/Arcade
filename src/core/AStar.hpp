/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** AStar
*/

#ifndef ASTAR_HPP_
#define ASTAR_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <list>

namespace Arcade
{
    typedef struct cellule_s
    {
        int status;
        int x;
        int y;
        int f_cost;
        int g_cost;
        int h_cost;
        struct cellule_s *neighbors;
        struct cellule_s *previous;
    } cellule_t;

    typedef struct nodes_s
    {
        cellule_t cellule;
        struct nodes_s *next;
        struct nodes_s *previous;
    } nodes_t;

    class AStar
    {
        public:
            AStar();
            ~AStar();

            std::vector<std::string> findWay(std::vector<std::string>, std::pair<int, int>, std::pair<int, int>);

        private:
            std::vector<std::string> _currentMap;
            int _cols;
            int _rows;
            cellule_t _start;
            cellule_t _end;
            std::vector<cellule_t *> _array;
            std::list<Arcade::nodes_t *> _garbage;
            std::list<Arcade::cellule_t *> _garbage_cellules;

            void create_array();
            void clear();
            void setup_neighbors(cellule_t **neighbors, int x, int y);
            void loop();
            void final_push(nodes_t *current);
            void set_neighbors(nodes_t **current);
            void foreach_neighbors(nodes_t *current, nodes_t **open);
            void *addToGarbage(size_t size, int status);
            void spe_push(Arcade::cellule_t **neighbor, int y, int x);
            void push(Arcade::nodes_t **nodes, Arcade::cellule_t cellule);
    };
}

#endif /* !ASTAR_HPP_ */
