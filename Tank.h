#ifndef _TANK_H_
#define _TANK_H_
#include "Bomb.h"
#include "Constants.h"
#include "Game.h"
#include "Item.h"
#include <cstdlib>
class Tank : public LivingEntity {
    bool is_super;
    bool is_laser;
    static int tank_num_left;

    // only for super.
    // max value
    int mine_count = 10;
    int mine_timer = 100;

  public:
    char *get_type() override {
        return "Tank";
    }
    bool isLaser() {
        return is_laser;
    }
    static void init() {
        tank_num_left = 20;
    }
    static int get_num_left() {
        return tank_num_left;
    }
    Tank(Game *g, int r, int c, bool is_super)
        : LivingEntity(r, c, g, NoneDirection), is_super(is_super) {
        this->is_super = tank_num_left % 4 == 0;
        is_laser = tank_num_left % 10 == 0;
        if (is_laser) {
            this->is_super = true;
        }

        tank_num_left--;
        is_out = false;
        max_health = this->is_super ? 4 : 1;
        health = max_health;
    }

    void normal_update() {
        int rn = rand() % 10;
        if (rn >= 0 && rn <= 6)
            return;
        if (rn == 7)
            dir = Direction((dir + 1) % 4);
        if (rn == 8)
            dir = Direction((dir + 1) % 4);
        if (rn == 9)
            dir = Direction((dir + 2) % 4);
        // dir = Direction();
    }

    void super_update() {
        if (mine_timer > 0) {
            mine_timer--;
        } else {
            mine_timer = 100;
            if (mine_count < 10)
                mine_count++;
        }
        int randomNumber = rand();
        if (randomNumber % 6 != 0) {
            dir = NoneDirection;
            // 1/6 chance to follow player
            return;
        }
        randomNumber = rand();
        if (randomNumber % 10 == 0 && mine_count > 0) {
            game->add_mine(row, col);
            mine_count--;
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

        if (is_laser && rand() % 100 <= 5) {
            game->add_laser(row, col, dir);
        }

        move();
        int randomNumber = rand() % 99;
        if (randomNumber <= 2) {
            int dx = 0;
            if (dir == Left) {
                dx = -1;
            } else if (dir == Right) {
                dx = 1;
            }
            game->add_bullet(row, col + dx, dir, get_type());
            // game->add_bomb(row, col);
        }

        auto color = is_super ? Gui::SuperTank : Gui::NormalTank;
        game->paintat(row, col - 1, 'C', color);
        game->paintat(row, col, 'E' - health, color);
        game->paintat(row, col + 1, 'D', color);
        is_super ? game->paintat(row - 1, col, '!') : void();
    }
    bool out() {
        return is_out;
    }
};
#endif
