#ifndef _TANK_H_
#define _TANK_H_
#include "Bomb.h"
#include "Game.h"
#include "Item.h"
#include <cstdlib>
class Tank : public Item {
    bool disabled;
    bool is_super;

  public:
    Tank(Game *g, size_t row) : Item(g), disabled(false) {
        row = 3;
        col = 2;
        srand(time(0));
    }
    void disable() {
        if (is_super) return;
        disabled = false;
    }

    void update(int key) {
        if (disabled) return;
        int randomNumber = rand() % 4;
        switch (randomNumber) {
            case 1:
                if (col > 0) {
                    col--;
                }
                break;
            case 2:
                if (col < 80) {
                    col++;
                }
                break;
            case 3:
                if (row > 0) {
                    row--;
                }
                break;
            case 4:
                if (row < 30) {
                    row++;
                }
                break;
        }        

        randomNumber = rand() % 99;
        if (randomNumber <= 2) {
            game->add_bomb(row, col);
        }

        game->paintat(row, col-1,  'C');
        game->paintat(row, col,  is_super ? 'X' : 'O');

        game->paintat(row, col,  'D');
    }
    bool out() {
        return false;
    }
};
#endif
