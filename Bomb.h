#ifndef _BOMB_H_
#define _BOMB_H_
#include "Constants.h"
#include "Game.h"
#include "Item.h"
#include "Player.h"
#include <cmath>
#include <cstddef>
class Bomb : public Item {
    bool is_out;

  public:
    // stage from 4 to 66
    Bomb(Game *g, size_t r, size_t c) : Item(g) {
        type = "Bomb";
        is_out = false;
        row = r;
        col = c;
    }
    void update(int key) {
        if (game->player->row == row && game->player->col == col){
            is_out = true;
            game->complete();
        }
        game->paintat(row, col, 'Q');
        row += 1;
        if (row >= MAX_ROW) {
            is_out = true;
        }
    }
    bool out() {
        return is_out;
    }
};
#endif
