#ifndef _BULLET_H_
#define _BULLET_H_
#include "Game.h"
#include "Item.h"
#include <memory>

class Bullet : public Item {
    Direction dir;
  public:
    Bullet(size_t r, size_t c, Game *game, Direction d) : Item(game), dir(d) {
        type = "Bullet";
        row = r;
        col = c;
        is_out = false;
    }
    void update(int key);
    bool out();
};
#endif
