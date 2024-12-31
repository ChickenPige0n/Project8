#include "Constants.h"
#include "Game.h"
#include "Item.h"
#include "Player.h"
#include <iostream>
using namespace std;

void Player::update(int key) {

    if (bullet_timer > 0) {
        bullet_timer--;
    } else {
        bullet_timer = 40;
        if (bullet_count < 20)
            bullet_count++;
    }

    int shoot = 0;
    // handle input key
    switch (key) {
    case KEY_LEFT:
    case 'a':
        if (dir == Right)
            dir = NoneDirection;
        else
            dir = Left;
        break;
    case KEY_RIGHT:
    case 'd':
        if (dir == Left)
            dir = NoneDirection;
        else
            dir = Right;
        break;
    case KEY_UP:
    case 'w':
        if (dir == Down)
            dir = NoneDirection;
        else
            dir = Up;
        break;
    case KEY_DOWN:
    case 's':
        if (dir == Up)
            dir = NoneDirection;
        else
            dir = Down;
        break;
    case ' ':
        shoot = 1;
        break;
    default:
        break;
    }
    move();
    // handle shooting
    if (shoot == 1 && bullet_count > 0) {
        bullet_count--;
        game->add_bullet(row, col, dir, get_type());
    }
    game->paintat(row, col, 'M', Gui::Player);
    int len = (health / 10.) * (MAX_COL - MIN_COL - 1);
    for (int i = 0; i < len; i++) {
        game->paintat(0, MIN_COL + i + 1, '+');
    }
}

Direction Player::get_dir() {
    return dir;
}