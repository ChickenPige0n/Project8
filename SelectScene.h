#ifndef _SELECTSCENE_H_
#define _SELECTSCENE_H_
#include "Gui.h"
#include <curses.h>
#include <math.h>
class SelectScene {
    double time;
    int selection;
    Gui gui;

  public:
    SelectScene() {
        selection = 1;
        gui.init();
    }
    ~SelectScene() {}
    int update() {
        time += 0.5;
        time = fmod(time, 2 * M_PI);
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
        gui.printMsg(19, 40, "Random Map");
        gui.printMsg(20, 40, "Custom Map");

        for (int i = 0; i < 11; i++) {
            gui.paintat(9.5 + sin(time + i), 15 + (i * 6), "TANK BATTLE"[i]);
        }

        gui.paintat(18 + selection, 38, 'o');
        gui.redraw();
        if (c == 'c') {
            return selection;
        }
        return -1;
    }
};

#endif