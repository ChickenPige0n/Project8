#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Constants.h"
#include "Game.h"
#include "Item.h"

class Player : public Item {
    Direction dir;
  public:
    Player(Game *g) : Item(g) {
        row = MAX_ROW / 2;
        col = MAX_COL / 2;
        dir = None;
    }
    bool out() override {
        return false;
    }
    void update(int key);
};
#endif
