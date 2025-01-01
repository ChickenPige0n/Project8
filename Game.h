#ifndef _GAME_H_
#define _GAME_H_
#include "BitGrid.h"
#include "Constants.h"
#include "Direction.h"
#include "Gui.h"
#include <array>
#include <cmath>
#include <list>
using namespace std;
class Laser;
class Item;
class Tank;
class Bullet;
class Player;
class Bomb;
// battlefield size 30x80
// 20 enemy with 4 super inside
// 1 player
class Game {
    Gui gui;
    array<array<int, 2>, 20> spawn_points;
    array<int, 2> player_ori;
    list<Item *> items;
    list<Tank *> tanks;
    int score;
    bool read_map;

  public:
    BitGrid obstacle_grid;
    Player *player;

    Game(bool read_map = false);
    ~Game() {
        auto ii = items.begin();
        while (ii != items.end()) {
            delete *ii;
            ii = items.erase(ii);
        }
        gui.end();
    }
    bool query_hit(Bullet *bullet);
    bool query_hit(Laser *laser, int row, int col);

    template <typename T> list<T *> get_items();
    template <typename T> void remove_all();

    void add_bullet(size_t r, size_t c, Direction d, char *source);
    void add_bomb(size_t r, size_t c);
    void add_mine(size_t r, size_t c);
    void add_laser(size_t r, size_t c, Direction d);
    void update();
    void complete(bool win);
    void paintat(size_t ro, size_t cl, char c) {
        gui.paintat(ro, cl, c);
    }
    void paintat(size_t ro, size_t cl, char c, Gui::Color color) {
        gui.paintat(ro, cl, c, color);
    }
};
#endif
