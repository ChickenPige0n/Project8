#ifndef _GAME_H_
#define _GAME_H_
#include "Direction.h"
#include "Gui.h"
#include <cmath>
#include <list>
using namespace std;
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
    list<Item *> items;
    list<Tank *> tanks;
    int score;

  public:
    Player *player;

    int bullet_count;
    int bullet_timer;

    Game();
    ~Game() {
        auto ii = items.begin();
        while (ii != items.end()) {
            delete *ii;
            ii = items.erase(ii);
        }
        gui.end();
    }
    bool query_hit(Bullet *bullet);

    template <typename T> list<T *> get_items();
    template <typename T> void remove_all();

    void add_bullet(size_t r, size_t c, Direction d);
    void add_bomb(size_t r, size_t c);
    void update();
    void complete();
    void paintat(size_t ro, size_t cl, char c) {
        gui.paintat(ro, cl, c);
    }
    void paintat(size_t ro, size_t cl, char c, Gui::Color color) {
        gui.paintat(ro, cl, c, color);
    }
};
#endif
