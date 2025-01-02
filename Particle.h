#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "Item.h"
#include <cstdlib>
class Particle : public Item {
    int timer;
    int dx;
    int dy;
    char display;

  public:
    Particle(Game *g, int r, int c, char display) : Item(g), display(display) {
        row = r;
        col = c;
        timer = 6;
        dx = rand() % 2 == 0 ? 1 : -1;
        dy = rand() % 2 == 0 ? 1 : -1;
    }
    void update(int key) override {
        if (timer <= 0 || (row >= MAX_ROW || row <= MIN_ROW || col >= MAX_COL ||
                           col <= MIN_COL)) {
            is_out = true;
            return;
        }
        timer--;
        row += dx;
        col += dy;
        game->paintat(row, col, display);
    }
};

#endif