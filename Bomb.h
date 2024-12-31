#ifndef _BOMB_H_
#define _BOMB_H_
#include "Constants.h"
#include "Game.h"
#include "Item.h"
#include "Player.h"
#include <cmath>
#include <cstddef>
class Bomb : public Item {

  public:
    // stage from 4 to 66
    Bomb(Game *g, size_t r, size_t c) : Item(g) {
        type = "Bomb";
        is_out = false;
        row = r;
        col = c;
        dir = Down;
    }
    void update(int key) {
        auto pl = game->player;
        if (pl->row == row && pl->col == col) {
            pl->hit(1);
            is_out = true;
        }
        game->paintat(row, col, 'Q');
        move();
        if (row >= MAX_ROW) {
            is_out = true;
        }
    }
    bool out() {
        return is_out;
    }
};
#endif
