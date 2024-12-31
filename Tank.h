#ifndef _TANK_H_
#define _TANK_H_
#include "Bomb.h"
#include "Game.h"
#include "Item.h"
#include <cstdlib>
class Tank : public Item {
    bool is_out;
    bool is_super;

  public:
    Tank(Game *g, int r, int c) : Item(g), is_out(false) {
        row = r;
        col = c;
    }
    void disable() {
        if (is_super) return;
        is_out = true;
    }

    void update(int key) {
        if (is_out) return;
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

        randomNumber = rand() % 99;
        if (randomNumber <= 20) {
            game->add_bomb(row, col);
        }

        game->paintat(row, col-1,  'C');
        game->paintat(row, col,  is_super ? 'X' : 'O');

        game->paintat(row, col+1,  'D');
    }
    bool out() {
        return is_out;
    }
};
#endif
