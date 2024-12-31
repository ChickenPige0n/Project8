#ifndef _HEALTHPACK_H_
#define _HEALTHPACK_H_
#include "Game.h"
#include "Item.h"
#include "Player.h"
#include <cmath>
#include <cstddef>
#include <cstdlib>
class HealthPack : public Item {
    int timer;

  public:
    char *get_type() override {
        return "HealthPack";
    }
    // stage from 4 to 66
    HealthPack(Game *g, size_t r, size_t c) : Item(g) {
        row = r;
        col = c;
        is_out = false;
        timer = 600;
    }
    void update(int key) {
        timer--;
        if (timer <= 0) {
            is_out = true;
            return;
        }
        game->paintat(row, col, '+', Gui::Color::SuperTank);
        auto pl = game->player;
        if (abs(pl->row - row) <= 1 && abs(pl->col - col) <= 1) {
            is_out = true;
            pl->heal(50);
        }
    }
    bool out() {
        return is_out;
    }
};
#endif