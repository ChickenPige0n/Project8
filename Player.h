#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Constants.h"
#include "Game.h"
#include "Item.h"
#include "LivingEntity.h"

class Player : public LivingEntity {
    Direction dir;
  public:
    Player(Game *g) : LivingEntity(MAX_ROW / 2, MAX_COL / 2, g, None) {
        type = "Player";
        health = 10;
    }
    Direction get_dir();
    bool out() override {
        return false;
    }
    void update(int key);
};
#endif
