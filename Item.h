#ifndef _ITEM_H_
#define _ITEM_H_
#include "Game.h"
#include <memory>
// Item base class
class Item {
  protected:
    char* type;
  public:
    enum Direction {
        Up,
        Down,
        Left,
        Right,
        None
    };
    int row;
    int col;
    Game *game;
    Item(Game *g) : game(g) {}
    virtual ~Item() = default;
    virtual void update(int key) {
        return;
    }
    virtual bool out() {
        return false;
    }
};
#endif
