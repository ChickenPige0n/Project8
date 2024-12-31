#ifndef _LASER_H_
#define _LASER_H_
#include "Game.h"
#include "Item.h"
#include <memory>

class Laser : public Item {
    int timer;

  public:
    char *damageSource;
    char *get_type() override {
        return "Laser";
    }
    Laser(size_t r, size_t c, Game *game, Direction d) : Item(game) {
        row = r;
        col = c;
        dir = d;
        is_out = false;
        timer = 3;
    }
    void update(int key) {
        if (timer <= 0) {
            is_out = true;
            return;
        }
        auto judge_hit = [this](Game *game, int row, int col) {
            if (timer == 3)
                game->query_hit(this, row, col);
        };
        if (dir == Up) {
            for (int i = row; i >= MIN_ROW; i--) {
                game->paintat(i, col, '^', Gui::Bullet);
                judge_hit(game, i, col);
            }
        } else if (dir == Down) {
            for (int i = row; i <= MAX_ROW; i++) {
                game->paintat(i, col, 'v', Gui::Bullet);
                judge_hit(game, i, col);
            }
        } else if (dir == Left) {
            for (int i = col; i >= MIN_COL; i--) {
                game->paintat(row, i, '<', Gui::Bullet);
                judge_hit(game, row, i);
            }
        } else if (dir == Right) {
            for (int i = col; i <= MAX_COL; i++) {
                game->paintat(row, i, '>', Gui::Bullet);
                judge_hit(game, row, i);
            }
        }
        timer--;
    }
    bool out() {
        return is_out;
    }
};
#endif