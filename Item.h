#ifndef _ITEM_H_
#define _ITEM_H_
#include "Constants.h"
#include "Game.h"
#include "Direction.h"
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
        switch (dir) {
        case Up:
            if (row > MIN_ROW)
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
        case NoneDirection:
            break;
        }
    }

  protected:
    Direction dir;
    char *type;
    bool is_out;
};
#endif
