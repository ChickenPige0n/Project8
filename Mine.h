#ifndef _MINE_H_
#define _MINE_H_
#include "Game.h"
#include "Item.h"
#include "Player.h"
#include <cmath>
#include <cstddef>
#include <cstdlib>
class Mine : public Item {
  public:
    char *get_type() override {
        return "Mine";
    }
    // stage from 4 to 66
    Mine(Game *g, size_t r, size_t c) : Item(g) {
        row = r;
        col = c;
    }
    void update(int key) {
        game->paintat(row, col, '#', Gui::Color::SuperTank);
        auto pl = game->player;
        if (abs(pl->row - row) <= 1 && abs(pl->col - col) <= 1) {
            is_out = true;
            pl->hit(5);
        }
    }
    bool out() {
        return is_out;
    }
};
#endif
