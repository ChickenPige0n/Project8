#ifndef _GUI_H_
#define _GUI_H_
#include <ncurses.h>

class Gui {
    size_t row;
    size_t col;
    WINDOW *win;
    bool colored;

  public:
    enum Color { NormalTank = 1, SuperTank, Player, Bullet };
    Gui() : row(20), col(50) {
        colored = has_colors();
        if (colored) {
            start_color();
            init_pair(1, COLOR_YELLOW, COLOR_GREEN); // normal tank
            init_pair(2, COLOR_CYAN, COLOR_BLUE);    // super tank
            init_pair(3, COLOR_BLACK, COLOR_WHITE);  // player
            init_pair(4, COLOR_RED, COLOR_MAGENTA);  // bullet
        }
        init();
    }
    ~Gui() {
        endwin();
    }
    void init();
    int get();
    void paintat(size_t, size_t, char);
    void paintat(size_t, size_t, char, Color);
    void printMsg(int row, int col, const char *prompt, int v);
    void printMsg(int row, int col, const char *prompt);
    void clear();
    void end() {
        endwin();
    }
};
#endif
