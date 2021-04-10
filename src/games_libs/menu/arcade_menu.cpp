/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-leo.sarochar
** File description:
** arcade_menu
*/

#include "arcade_menu.hpp"
#include <regex>

static const std::regex rgx("(\\w+)\\s+(\\w+)");

Arcade::Game_Menu::Game_Menu(): AGameModule()
{
}

void Arcade::Game_Menu::init_sprites()
{
    graphical_sprite_t sprite;
    int id = 0;

    sprite.visible = 1;
    sprite.size = {0, 0, 0};
    sprite.angle = 0;
    for (auto &n: _texts) {
        sprite.id = id;
        sprite.path = "ressources/" + n.text + "_logo.png";
        sprite.pos = {WIDTH / 2, HEIGHT / 4, 0};
        sprite.ncursesBox = 1;
        sprite.color = {255, 0, 0, {RED, BLACK}};
        id += 1;
        _sprites.push_back(sprite);
        nbGames += 1;
    }
    sprite.id = id;
    sprite.path = "ressources/arrow_left.png";
    sprite.color = {0, 255, 0, {CYAN, BLACK}};
    sprite.pos = {120, HEIGHT / 2 + 30, 0};
    _sprites.push_back(sprite);
    sprite.id = ++id;
    sprite.pos = {WIDTH - 120, HEIGHT / 2 + 30, 0};
    sprite.path = "ressources/arrow_right.png";
    _sprites.push_back(sprite);
    sprite.id = ++id;
    sprite.pos = {WIDTH / 2, HEIGHT / 2 + 200, 0};
    sprite.path = "ressources/start_button.png";
    sprite.color = {0, 0, 255, {BLUE, BLACK}};
    _sprites.push_back(sprite);
    sprite.id = ++id;
    sprite.pos = {WIDTH / 2, HEIGHT / 2 + 400, 0};
    sprite.path = "ressources/exit_button.png";
    sprite.color = {0, 0, 255, {BLUE, BLACK}};
    _sprites.push_back(sprite);
}

Arcade::Game_Menu::~Game_Menu()
{

}

void Arcade::Game_Menu::updateLeaderBoard()
{
    std::string path("ressources/" + _texts[_gindex].text + "/highscore.txt");
    std::ifstream fs(path);
    int index = 1;

    _leaderboard.clear();
    if (fs.is_open()) {
        std::string str;
        while (std::getline(fs, str)) {
            std::smatch matches;
            std::regex_search(str, matches, rgx);
            _leaderboard[std::stoi(matches[2])] = matches[1];
        }
    }
    _texts[_texts.size() - 1].text = "1. ";
    _texts[_texts.size() - 2].text = "2. ";
    _texts[_texts.size() - 3].text = "3. ";
    if (!_leaderboard.empty()) {
        for (std::map<int, std::string>::iterator it = --_leaderboard.end(); index != 4; --it) {
            _texts[_texts.size() - index].text += it->second + ": " + std::to_string(it->first);
            index += 1;
            if (it == _leaderboard.begin())
                break;
        }
    }
}

void Arcade::Game_Menu::startGame()
{
    graphical_text_t text;
    int index = 0;
    float x = 100;
    float y = 100;
    int i = 0;
    _gindex = 0;
    _choiceIndex = 0;
    nbGames = 0;

    for (const auto & entry : std::filesystem::directory_iterator("lib")) {
        if (entry.path() == "lib/arcade_sfml.so" || entry.path() == "lib/arcade_sdl2.so" || entry.path() == "lib/arcade_ncurses.so" || entry.path() == "lib/arcade_menu.so" || entry.path() == "lib/.gitkeep")
            continue;
        std::string path(entry.path());
        index = path.find(".so");
        text.id = i;
        text.text = std::string(path.substr(11, index - 11));
        text.pos = {x, y, 0};
        text.color = {0, 0, 255, {Arcade::COLOR::BLUE, Arcade::COLOR::BLACK}};
        text.size = 24;
        text.font = "ressources/font.ttf";
        _texts.push_back(text);
        y += 100;
        i++;
    }
    _box.pos = {WIDTH / 2, HEIGHT / 2 + 50, 0};
    _box.size = {WIDTH / 10, HEIGHT / 15, 0};
    init_sprites();
    text.color = {0, 0, 255, {Arcade::COLOR::BLUE, Arcade::COLOR::BLACK}};
    text.size = 24;
    text.font = "ressources/font.ttf";
    text.id = i++;
    text.text = "Press F1/F2 to change libraries";
    text.pos = {20, 800, 0};
    _texts.push_back(text);
    text.id = i++;
    text.text = "Press F3/F4 to change game in runtime";
    text.pos = {20, 824, 0};
    _texts.push_back(text);
    text.id = i++;
    text.text = "Press F5 to restart game";
    text.pos = {20, 848, 0};
    _texts.push_back(text);
    text.id = i++;
    text.text = "Press F6 to go to menu";
    text.pos = {20, 872, 0};
    _texts.push_back(text);
    text.id = i++;
    text.text = "Press F7 to quit";
    text.pos = {20, 896, 0};
    _texts.push_back(text);
    text.id = i++;
    text.text = "Use space and keyboard arrow keys to play game and move in menu";
    text.pos = {20, 920, 0};
    _texts.push_back(text);
    text.id = i++;
    text.text = "3. ";
    text.pos = {1500, 150, 0};
    _texts.push_back(text);
    text.id = i++;
    text.text = "2. ";
    text.pos = {1500, 100, 0};
    _texts.push_back(text);
    text.id = i++;
    text.text = "1. ";
    text.pos = {1500, 50, 0};
    _texts.push_back(text);
    updateLeaderBoard();
}

void Arcade::Game_Menu::updatePlayerName()
{
    char ch = 0;

    for (int index = Arcade::KEYS::A; index <= Arcade::KEYS::Z; index += 1) {
        if (_keys[index] && _playerName.size() < 10) {
            ch = index - Arcade::KEYS::A + 'a';
            _playerName.insert(_playerName.end(), 1, ch);
        }
    }
    if (_keys[Arcade::KEYS::BACKSPACE] && _playerName.length() > 0)
        _playerName.erase(_playerName.length() - 1, 1);
}

int Arcade::Game_Menu::updateGame(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *list)
{
    int ret_1 = 0;
    int ret_2 = 0;

    updatePlayerName();
    if (_keys[Arcade::KEYS::ARROW_LEFT])
        _gindex = _gindex >= 1 ? _gindex - 1 : nbGames - 1;
    if (_keys[Arcade::KEYS::ARROW_RIGHT])
        _gindex = (_gindex + 1) < nbGames ? _gindex + 1 : 0;
    if (_keys[Arcade::KEYS::ARROW_DOWN] || _keys[Arcade::KEYS::ARROW_UP])
        _choiceIndex = _choiceIndex == 1 ? 0 : 1;
    if (_keys[Arcade::KEYS::RETURN]) {
        return (_choiceIndex == 0) ? (_gindex + 1) : -1;
    }
    _box.input = _playerName;
    ret_1 = isMouseOnSpriteHitbox(_sprites[_sprites.size() - 2]);
    if (ret_1) {
        _choiceIndex = 0;
        if (_keys[Arcade::KEYS::MOUSE])
            ret_1 = _gindex + 1;
    }
    ret_2 = isMouseOnSpriteHitbox(_sprites[_sprites.size() - 1]);
    if (ret_2) {
        _choiceIndex = 1;
        if (_keys[Arcade::KEYS::MOUSE])
            ret_2 = -1;
    }
    updateLeaderBoard();
    draw(list);
    return (ret_1 != 0 && _keys[Arcade::KEYS::MOUSE]) ? ret_1 : (ret_2 != 0 && _keys[Arcade::KEYS::MOUSE]) ? ret_2 : 0;
}

void Arcade::Game_Menu::draw(std::list<std::pair<Arcade::FLAGS, IStruct_t *>> *list)
{
    size_t index = 0;
    size_t text_index = 0;
    size_t previous_index = 0;
    size_t next_index = 0;
    size_t temp = 0;

    next_index = (_gindex + 1 >= nbGames) ? 0 : _gindex + 1;
    previous_index = (_gindex == 0) ? nbGames - 1 : _gindex - 1;
    for (auto &n: _sprites) {
        if (index == _gindex || index >= nbGames) {
            if (n.path == "ressources/start_button.png" || n.path == "ressources/exit_button.png") {
                if (temp == _choiceIndex)
                    n.color = {0, 0, 255, {YELLOW, BLACK}};
                else
                    n.color = {0, 255, 255, {BLUE, BLACK}};
                temp += 1;
            }
            list->push_back(std::make_pair(SPRITE, &n));
        }
        index += 1;
    }
    for (auto &n: _texts) {
        if (text_index == next_index) {
            n.pos.y = HEIGHT / 2 - 100;
            n.pos.x = WIDTH - 200;
            list->push_back(std::make_pair(TEXT, &n));
        }
        if (text_index == previous_index) {
            n.pos.y = HEIGHT / 2 - 100;
            n.pos.x = 40;
            list->push_back(std::make_pair(TEXT, &n));
        }
        if (text_index > nbGames - 1)
            list->push_back(std::make_pair(TEXT, &n));
        text_index += 1;
    }
    list->push_back(std::make_pair(BOX, &_box));
}

extern "C" Arcade::IGameModule *entryPoint(void)
{
    return new Arcade::Game_Menu;
}