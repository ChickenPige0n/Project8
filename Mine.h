#ifndef _BOMB_H_
#define _BOMB_H_
#include "Game.h"
#include "Item.h"
#include "Player.h"
#include <cmath>
#include <cstddef>
#include <cstdlib>
class Mine : public Item {
    bool is_out;

  public:
    // stage from 4 to 66
    Mine(Game *g, size_t r, size_t c) : Item(g) {
        row = r;
        col = c;
    }
    void update(int key) {
        if (abs(game->player->row -= row) <= 1 && abs(game->player->col == col) <= 1){
            is_out = true;
            // game->complete();
        }
    }
    bool out() {
        return is_out;
    }
};
#endif
