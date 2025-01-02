#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Constants.h"
#include "Game.h"
#include "Item.h"
#include "LivingEntity.h"

class Player : public LivingEntity {
  public:
    int bullet_count;
    int bullet_timer;

    void reset();

    char *get_type() override {
        return "Player";
    }
    Player(Game *g) : LivingEntity(MAX_ROW / 2, MAX_COL / 2, g, NoneDirection) {
        max_health = 10;
        health = max_health;
        bullet_count = 10;
        bullet_timer = 40;
    }
    Player(Game *g, int row, int col)
        : LivingEntity(row, col, g, NoneDirection) {
        max_health = 10;
        health = max_health;
        bullet_count = 10;
        bullet_timer = 40;
    }
    void hit(int damage) override {
        LivingEntity::hit(damage);
        game->shake_screen();
    }
    bool out() override {
        return false;
    }
    void update(int key);
};
#endif
