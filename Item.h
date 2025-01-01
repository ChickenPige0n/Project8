#ifndef _ITEM_H_
#define _ITEM_H_
#include "Constants.h"
#include "Direction.h"
#include "Game.h"
#include <memory>
// Item base class
class Item {
  public:
    int row;
    int col;
    Game *game;
    Item(Game *g) : game(g) {}
    void queue_delete() {
        is_out = true;
    }
    virtual ~Item() = default;
    virtual void update(int key) {
        return;
    }
    virtual bool out() {
        return false;
    }
    void move() {
        auto ob = game->obstacle_grid;
        switch (dir) {
        case Up:
            if (row > MIN_ROW) {
                if (ob.get(row - 1, col)) {
                    dir = NoneDirection;
                    return;
                }
                row--;
            }
            if (row == MIN_ROW) {
                dir = NoneDirection;
            }
            break;
        case Down:
            if (row < MAX_ROW) {
                if (ob.get(row + 1, col)) {
                    dir = NoneDirection;
                    return;
                }
                row++;
            }
            if (row == MAX_ROW) {
                dir = NoneDirection;
            }
            break;
        case Left:
            if (col > MIN_COL) {
                if (ob.get(row, col - 1)) {
                    dir = NoneDirection;
                    return;
                }
                col--;
            }
            if (col == MIN_COL) {
                dir = NoneDirection;
            }
            break;
        case Right:
            if (col < MAX_COL) {
                if (ob.get(row, col + 1)) {
                    dir = NoneDirection;
                    return;
                }
                col++;
            }
            if (col == MAX_COL) {
                dir = NoneDirection;
            }
            break;
        case NoneDirection:
            break;
        }
    }
    virtual char *get_type() {
        return "Item";
    }
    Direction get_dir() {
        return dir;
    }

  protected:
    Direction dir;
    bool is_out;
};
#endif
