#include "Bullet.h"
#include "Constants.h"
#include "Game.h"

void Bullet::update(int key) {
    switch (dir) {
    case Up:
        row--;
        break;
    case Down:
        row++;
        break;
    case Left:
        col--;
        break;
    case Right:
        col++;
        break;
    case None:
        break;
    }
    if (col > MAX_COL || row < 0 || row > MAX_ROW || col < MIN_COL) {
        is_out = true;
        return;
    }
    if (game->query_hit(this)) {
        is_out = true;
        return;
    }
    game->paintat(row, col, '*');
}

bool Bullet::out() {
    return row <= 0 || is_out;
}
