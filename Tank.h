#ifndef _TANK_H_
#define _TANK_H_
#include "Bomb.h"
#include "Game.h"
#include "Item.h"
#include "Constants.h"
#include <cstdlib>

class Tank : public LivingEntity {
    Direction dir;
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
        int randomNumber = rand() % 5;
        switch (randomNumber) {
        case 0:
            dir = Left;
            break;
        case 1:
            dir = Right;
            break;
        case 2:
            dir = Up;
            break;
        case 3:
            dir = Down;
            break;
        case 4:
            dir = None;
            break;
        }
    }

    void super_update() {
        int randomNumber = rand();
        if (! randomNumber % 3) {
            // 1/3 chance to follow player
            return;
        }
        auto p = game->player;
        auto x_diff = p->row - row;
        auto y_diff = p->col - col;
        if (abs(x_diff) > abs(y_diff)) {
            if (x_diff > 0) {
                dir = Down;
            } else {
                dir = Up;
            }
        } else {
            if (y_diff > 0) {
                dir = Right;
            } else {
                dir = Left;
            }
        }
    }

    void update(int key) {
        if (is_out)
            return;
        is_super ? super_update() : normal_update();
        move();
        int randomNumber = rand() % 99;
        if (randomNumber <= 2) {
            game->add_bomb(row, col);
        }

        auto color = is_super ? Gui::SuperTank : Gui::NormalTank;
        game->paintat(row, col - 1, 'C', color);
        game->paintat(row, col, is_super ? 'X' : 'O', color);
        game->paintat(row, col + 1, 'D', color);
        game->paintat(row - 1, col, health + '0', color);
    }
    bool out() {
        return is_out;
    }
};
#endif
