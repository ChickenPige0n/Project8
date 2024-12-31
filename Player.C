#include "Constants.h"
#include "Game.h"
#include "Item.h"
#include "Player.h"
#include <iostream>
using namespace std;

void Player::update(int key) {
    int shoot = 0;
    // handle input key
    switch (key) {
    case KEY_LEFT:
    case 'a':
        if (dir == Right)
            dir = None;
        else
            dir = Left;
        break;
    case KEY_RIGHT:
    case 'd':
        if (dir == Left)
            dir = None;
        else
            dir = Right;
        break;
    case KEY_UP:
    case 'w':
        if (dir == Down)
            dir = None;
        else
            dir = Up;
        break;
    case KEY_DOWN:
    case 's':
        if (dir == Up)
            dir = None;
        else
            dir = Down;
        break;
    case ' ':
        shoot = 1;
        break;
    default:
        break;
    }
    // handle player movement
    switch (dir) {
    case Up:
        if (row > 0)
            row--;
        break;
    case Down:
        if (row < MAX_ROW)
            row++;
        break;
    case Left:
        if (col > MIN_COL)
            col--;
        break;
    case Right:
        if (col < MAX_COL)
            col++;
        break;
    case None:
        break;
    }

    // handle shooting
    if (shoot == 1)
        game->add_bullet(row, col);

    game->paintat(row, col, 'M');
}

Item::Direction Player::get_dir() {
    return dir;
}