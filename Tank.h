#ifndef _TANK_H_
#define _TANK_H_
#include "Bomb.h"
#include "Game.h"
#include "Item.h"
#include <cstdlib>

class Tank : public LivingEntity {
    bool is_super;

    // only for super.
    // max value
    int mine_count = 10;
    int mine_timer = 100;

  public:
    Tank(Game *g, int r, int c, bool is_super)
        : LivingEntity(r, c, g, None), is_super(is_super) {
        type = "Tank";
        is_out = false;
        health = is_super ? 4 : 1;
    }

    void normal_update() {
        int randomNumber = rand() % 4;
        switch (randomNumber) {
        case 0:
            if (col > 0) {
                col--;
            }
            break;
        case 1:
            if (col < 80) {
                col++;
            }
            break;
        case 2:
            if (row > 0) {
                row--;
            }
            break;
        case 3:
            if (row < 30) {
                row++;
            }
            break;
        }
    }
    void super_update() {
        int randomNumber = rand();
        if (randomNumber % 2) {
            return;
        }
        auto p = game->player;
        auto x_diff = p->row - row;
        auto y_diff = p->col - col;
        if (abs(x_diff) > abs(y_diff)) {
            if (x_diff > 0) {
                row++;
            } else {
                row--;
            }
        } else {
            if (y_diff > 0) {
                col++;
            } else {
                col--;
            }
        }
    }

    void update(int key) {
        if (is_out)
            return;

        is_super ? super_update() : normal_update();

        int randomNumber = rand() % 99;
        if (randomNumber <= 2) {
            game->add_bomb(row, col);
        }

        game->paintat(row, col - 1, 'C');
        game->paintat(row, col, is_super ? 'X' : 'O');
        game->paintat(row, col + 1, 'D');
    }
    bool out() {
        return is_out;
    }
};
#endif
