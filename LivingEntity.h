#ifndef _LIVINGENTITY_H_
#define _LIVINGENTITY_H_
#include "Game.h"
#include "Item.h"
#include <memory>

class LivingEntity : public Item {
  protected:
	int health;
  public:
	LivingEntity(size_t r, size_t c, Game *game, Direction d) : Item(game) {
		type = "LivingEntity";
		row = r;
		col = c;
		is_out = false;
	}

	void hit(int damage) {
		health -= damage;
		if (health <= 0) {
			if (type == "Player") {
				game->complete();
			}
			is_out = true;
		}
	}

	void heal(int amount) {
		health += amount;
	}
	void update(int key);
	bool out();
};

#endif