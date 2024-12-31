#ifndef _TANK_H_
#define _TANK_H_
#include "Bomb.h"
#include "Game.h"
#include "Item.h"
#include <cstdlib>
class Tank : public Item {
    bool is_super;

  public:
    Tank(Game *g, int r, int c) : Item(g) {
        type = "Tank";
        is_out = false;
        row = r;
        col = c;
    }
    void disable() {
        if (is_super)
            return;
        is_out = true;
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
