#include "Bullet.h"
#include "Game.h"

void Bullet::update(int key) {
    if (row <= 1)
        return;
    row--;
    if (game->query_hit(this)) {
            is_out = true;
            return;
    }
    game->paintat(row, col, '^');
}

bool Bullet::out() {
    return row <= 0 || is_out;
}
