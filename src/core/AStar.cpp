/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** AStar
*/

#include "AStar.hpp"

Arcade::AStar::AStar()
{
    _cols = 0;
}

Arcade::AStar::~AStar()
{
}

int get_h_cost(int x, int y, int x_f, int y_f)
{
    int x_n = 0;
    int y_n = 0;

    y_n = (y_f - y > 0) ? y_f - y : - (y_f - y);
    x_n = (x_f - x > 0) ? x_f - x : - (x_f - x);
    return (x_n + y_n);
}

Arcade::cellule_t init(int x, int y)
{
    Arcade::cellule_t cellule;

    cellule.status = 0;
    cellule.x = x;
    cellule.y = y;
    cellule.f_cost = 0;
    cellule.g_cost = 0;
    cellule.h_cost = 0;
    cellule.neighbors = nullptr;
    cellule.previous = nullptr;
    return (cellule);
}

void Arcade::AStar::spe_push(Arcade::cellule_t **neighbor, int y, int x)
{
    Arcade::cellule_t *newOne = new Arcade::cellule_t;
    Arcade::cellule_t *temp = *neighbor;

    _garbage_cellules.push_back(newOne);
    newOne->status = 0;
    newOne->x = x;
    newOne->y = y;
    newOne->f_cost = 0;
    newOne->g_cost = 0;
    newOne->h_cost = 0;
    newOne->neighbors = nullptr;
    if (!*neighbor) {
        newOne->previous = nullptr;
        *neighbor = newOne;
        return;
    }
    while (temp->neighbors)
        temp = temp->neighbors;
    temp->neighbors = newOne;
    newOne->previous = temp;
}

void Arcade::AStar::setup_neighbors(cellule_t **neighbors, int x, int y)
{
    if (y < _cols - 1 && _currentMap[y + 1][x] != 'x' && _currentMap[y + 1][x] != '#')
        spe_push(neighbors, y + 1, x);
    if (y > 0 && _currentMap[y - 1][x] != 'x' && _currentMap[y - 1][x] != '#')
        spe_push(neighbors, y - 1, x);
    if (x < _rows - 1 && _currentMap[y][x + 1] != 'x' && _currentMap[y][x + 1] != '#')
        spe_push(neighbors, y, x + 1);
    if (x > 0 && _currentMap[y][x - 1] != 'x' && _currentMap[y][x - 1] != '#')
        spe_push(neighbors, y, x - 1);
}

void Arcade::AStar::create_array()
{
    cellule_t *current;

    for (int index = 0; index < _cols; index += 1) {
        current = new cellule_t[_rows];
        for (int temp = 0; temp < _rows; temp += 1) {
            current[temp] = init(temp, index);
            if (_currentMap[index][temp] != 'x' && _currentMap[index][temp] != '#') {
                setup_neighbors(&current[temp].neighbors, temp, index);
            }
        }
        _array.push_back(current);
    }
}

void Arcade::AStar::clear()
{
    for (int index = 0; index < _cols; index += 1)
        delete[] _array[index];
    for (auto &n: _garbage)
        delete n;
    for (auto &n: _garbage_cellules)
        delete n;
    _array.clear();
    _garbage.clear();
    _garbage_cellules.clear();
}

Arcade::nodes_t *lowest_fcost(Arcade::nodes_t *open)
{
    int save_f = 1000000000;
    int check = 0;
    int winner = 0;

    for (Arcade::nodes_t *copy = open; copy; copy = copy->next) {
        if (copy->cellule.f_cost < save_f) {
            save_f = copy->cellule.f_cost;
            winner = check;
        }
        check += 1;
    }
    for (Arcade::nodes_t *copy = open; copy; copy = copy->next) {
        if (winner == 0)
            return (copy);
        winner -= 1;
    }
    return (nullptr);
}

void delete_node(Arcade::nodes_t **nodes, Arcade::nodes_t *ptr)
{
    if (!*nodes || !ptr)
        return;
    if (*nodes == ptr)
        *nodes = ptr->next;
    if (ptr->next)
        ptr->next->previous = ptr->previous;
    if (ptr->previous)
        ptr->previous->next = ptr->next;
}

void Arcade::AStar::push(Arcade::nodes_t **nodes, Arcade::cellule_t cellule)
{
    Arcade::nodes_t *newOne = new Arcade::nodes_t;
    Arcade::nodes_t *temp = *nodes;

    _garbage.push_back(newOne);
    newOne->cellule = cellule;
    newOne->next = nullptr;
    if (!*nodes) {
        newOne->previous = nullptr;
        *nodes = newOne;
        return;
    }
    while (temp->next)
        temp = temp->next;
    temp->next = newOne;
    newOne->previous = temp;
}

void Arcade::AStar::final_push(nodes_t *current)
{
    cellule_t temp = current->cellule;

    while (temp.previous) {
        _currentMap[temp.y].replace(temp.x, 1, "o");
        temp = *temp.previous;
    }
    _currentMap[temp.y].replace(temp.x, 1, "o");
}

void change_status(Arcade::cellule_t **neighbors, int y, int x)
{
    if (!neighbors)
        return;
    for (Arcade::cellule_t *copy = *neighbors; copy; copy = copy->neighbors) {
        if (copy->y == y && copy->x == x) {
            copy->status = 1;
            return;
        }
    }
}

void Arcade::AStar::set_neighbors(nodes_t **current)
{
    int x = (*current)->cellule.x;
    int y = (*current)->cellule.y;

    (*current)->cellule.neighbors = _array[y][x].neighbors;
    if (y < _cols - 1)
        change_status(&_array[y + 1][x].neighbors, y, x);
    if (y > 0)
        change_status(&_array[y - 1][x].neighbors, y, x);
    if (x < _rows - 1)
        change_status(&_array[y][x + 1].neighbors, y, x);
    if (x > 0)
        change_status(&_array[y][x - 1].neighbors, y, x);
}

int include(Arcade::nodes_t *nodes, Arcade::cellule_t cellule)
{
    for (Arcade::nodes_t *copy = nodes; copy; copy = copy->next)
        if (copy->cellule.x == cellule.x && copy->cellule.y == cellule.y)
            return (1);
    return (0);
}

int check_better(Arcade::nodes_t *current, Arcade::cellule_t *nei, Arcade::nodes_t **open)
{
    int tempG = 0;
    int check = 0;

    tempG = current->cellule.g_cost + 1;
    if (include(*open, *nei)) {
        if (tempG < nei->g_cost) {
            nei->g_cost = tempG;
            check = 2;
        }
    } else {
        nei->g_cost = tempG;
        check = 1;
    }
    return (check);
}

void Arcade::AStar::foreach_neighbors(nodes_t *current, nodes_t **open)
{
    cellule_t *nei = current->cellule.neighbors;
    int check = 0;

    for (; nei; nei = nei->neighbors) {
        if (!nei->status) {
            check = check_better(current, nei, open);
            if (check == 1 || check == 2) {
                nei->h_cost = get_h_cost(nei->x, nei->y, _end.x, _end.y);
                nei->f_cost = nei->g_cost + nei->h_cost;
                nei->previous = &current->cellule;
            }
            if (check == 1)
                push(open, *nei);
        }
    }
}

void Arcade::AStar::loop()
{
    nodes_t *open = nullptr;
    nodes_t *current = nullptr;

    push(&open, _start);
    while (open) {
        current = lowest_fcost(open);
        if (current && current->cellule.x == _end.x && \
        current->cellule.y == _end.y)
            return (final_push(current));
        delete_node(&open, current);
        set_neighbors(&current);
        foreach_neighbors(current, &open);
    }
}

std::vector<std::string> Arcade::AStar::findWay(std::vector<std::string> map, std::pair<int, int> start, std::pair<int, int> finish)
{
    _currentMap = map;
    _rows = _currentMap[0].length();
    _cols = _currentMap.size();
    create_array();
    _start = _array[start.second][start.first];
    _end = _array[finish.second][finish.first];
    loop();
    clear();
    return _currentMap;
}