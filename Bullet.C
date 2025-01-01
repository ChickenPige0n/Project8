#include "Bullet.h"
#include "Constants.h"
#include "Game.h"

void Bullet::update(int key) {
    move();
    if (col > MAX_COL || row < MIN_ROW || row > MAX_ROW || col < MIN_COL ||
        dir == NoneDirection) {
        is_out = true;
        return;
    }
    if (game->query_hit(this)) {
        is_out = true;
        return;
    }
    game->paintat(row, col, '*', Gui::Bullet);
}

bool Bullet::out() {
    return row <= 0 || is_out;
}
