#ifndef _BULLET_H_
#define _BULLET_H_
#include "Game.h"
#include "Item.h"
#include <memory>

class Bullet : public Item {

  public:
    char *damageSource;
    char *get_type() override {
        return "Bullet";
    }
    Bullet(size_t r, size_t c, Game *game, Direction d, char *source)
        : Item(game), damageSource(source) {
        row = r;
        col = c;
        dir = d;
        is_out = false;
    }
    void update(int key);
    bool out();
};
#endif
