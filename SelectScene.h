#ifndef _SELECTSCENE_H_
#define _SELECTSCENE_H_
#include "Gui.h"
#include <curses.h>
class SelectScene {
    int selection;
    Gui gui;

  public:
    SelectScene() {
        selection = 1;
        gui.init();
    }
    ~SelectScene() {}
    int update() {
        gui.clear();
        int c = gui.get();
        switch (c) {
        case 'w':
        case KEY_UP:
            selection = 1;
            break;
        case 's':
        case KEY_DOWN:
            selection = 2;
            break;
        }
        gui.printMsg(2, 10, "Select Gamemode");

        gui.printMsg(4, 10, "Press c to confirm");
        gui.printMsg(12, 40, "Random Map");
        gui.printMsg(13, 40, "Custom Map");
        gui.paintat(11 + selection, 38, 'o');
        gui.redraw();
        if (c == 'c') {
            return selection;
        }
        return -1;
    }
};

#endif