#ifndef _LIVINGENTITY_H_
#define _LIVINGENTITY_H_
#include "Game.h"
#include "Item.h"
#include <cstring>
#include <memory>

class LivingEntity : public Item {
  protected:
    int health;
    int max_health;

  public:
    char *get_type() override {
        return "LivingEntity";
    }
    LivingEntity(size_t r, size_t c, Game *game, Direction d) : Item(game) {
        row = r;
        col = c;
        is_out = false;
    }

    virtual void hit(int damage) {
        health -= damage;
        if (health <= 0) {
            if (strcmp(get_type(), "Player") == 0) {
                game->complete();
            }
            is_out = true;
        }
    }
    virtual int get_health() {
        return health;
    }

    virtual void heal(int amount) {
        health += amount;
        if (health > max_health) {
            health = max_health;
        }
    }
};

#endif