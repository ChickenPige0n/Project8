#include "Bomb.h"
#include "Bullet.h"
#include "Constants.h"
#include "Game.h"
#include "HealthPack.h"
#include "Laser.h"
#include "LivingEntity.h"
#include "Mine.h"
#include "Particle.h"
#include "Player.h"
#include "Tank.h"
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <curses.h>
#include <fstream>
#include <math.h>
#include <memory>
#include <unistd.h>

Game::Game(bool read_map) : obstacle_grid(BitGrid(MAX_ROW + 4, MAX_COL + 4)) {
    this->read_map = read_map;
    int size_r = MAX_ROW + 4;
    int size_c = MAX_COL + 4;
    if (!read_map) {
        player = new Player(this);
        for (int r = 0; r < size_r; r++) {
            for (int c = 0; c < size_c; c++) {
                obstacle_grid.set(r, c, rand() % 140 < 1);
            }
        }

    } else {
        fstream file("Map1.tkm");
        char ch;
        for (int r = MIN_ROW; r <= MAX_ROW; r++) {
            for (int c = MIN_COL; c <= MAX_COL; c++) {
                file >> ch;
                int index = 0;
                switch (ch) {
                case '#':
                    obstacle_grid.set(r, c, true);
                    break;
                case 'P':
                    player = new Player(this, r, c);
                    player_ori[0] = r;
                    player_ori[1] = c;
                    break;
                }
                if (ch <= '9' && ch >= '0') {
                    index = ch - '0';
                    spawn_points[index][0] = r;
                    spawn_points[index][1] = c;
                }
                if (ch <= 'j' && ch >= 'a') {
                    index = ch - 'a' + 10;
                    spawn_points[index][0] = r;
                    spawn_points[index][1] = c;
                }
            }
        }
    }
    Tank::init();
    gui.init();
    items.push_back(player);
    score = 0;
    srand(time(0));
}

void Game::add_bullet(size_t r, size_t c, Direction d, char *source) {
    d = d == NoneDirection ? Up : d;
    items.push_back(new Bullet(r, c, this, d, source));
}
void Game::add_bomb(size_t r, size_t c) {
    items.push_back(new Bomb(this, r, c));
}
void Game::add_mine(size_t r, size_t c) {
    items.push_back(new Mine(this, r, c));
}
void Game::add_laser(size_t r, size_t c, Direction d) {
    items.push_back(new Laser(r, c, this, d));
}
void Game::add_particle(size_t r, size_t c, char display) {
    items.push_back(new Particle(this, r, c, display));
}

void Game::shake_screen() {
    gui.shake();
}

void Game::update() {
    gui.clear();
    gui.printMsg(2, 68, "Bullet", player->bullet_count);
    gui.printMsg(3, 68, "Score", score);
    int tank_tobe_shown = Tank::get_num_left();
    int tank_left = tank_tobe_shown + get_items<Tank>().size();
    gui.printMsg(4, 68, "Tank Left", tank_left);
    if (tank_left == 0) {
        complete(true);
    }

    if (get_items<Tank>().size() < 4 && tank_tobe_shown > 0) {
        int row;
        int col;
        if (!read_map) {
            row = rand() % (MAX_ROW - MIN_ROW - 10) + 5;
            col = rand() % (MAX_COL - MIN_COL - 20) + 10;
        } else {
            row = spawn_points[tank_tobe_shown - 1][0];
            col = spawn_points[tank_tobe_shown - 1][1];
        }
        items.push_back(new Tank(this, row, col, true));
    }

    int r = rand() % 100;
    if (r < 1) {
        int row = rand() % (MAX_ROW - MIN_ROW - 10) + 5;
        int col = rand() % (MAX_COL - MIN_COL - 10) + 5;
        items.push_back(new HealthPack(this, row, col));
    }

    int c = gui.get();
    list<Item *>::iterator bi = items.begin();
    while (bi != items.end()) {
        (*bi)->update(c);

        if ((*bi)->out()) {
            delete *bi;
            bi = items.erase(bi);
        } else {
            bi++;
        }
    }

    for (int r = MIN_ROW; r <= MAX_ROW; r++) {
        for (int c = MIN_COL; c <= MAX_COL; c++) {
            if (obstacle_grid.get(r, c)) {
                gui.paintat(r, c, '#');
            }
        }
    }
    gui.redraw();
}

bool Game::query_hit(Bullet *bullet) {
    for (auto enitiy : get_items<LivingEntity>()) {
        int width = strcmp(enitiy->get_type(), "Player") == 0 ? 1 : 2;
        if (bullet->row == enitiy->row &&
            abs(bullet->col - enitiy->col) < width) {
            if (strcmp(bullet->damageSource, "Player") == 0)
                score += 100;
            enitiy->hit(1);
            return true;
        }
    }
    return false;
}

bool Game::query_hit(Laser *laser, int row, int col) {
    for (auto enitiy : get_items<LivingEntity>()) {
        auto etype = enitiy->get_type();
        int width = strcmp(etype, "Player") == 0 ? 1 : 2;
        if (row == enitiy->row && abs(col - enitiy->col) < width) {
            if (strcmp(etype, "Player") == 0) {
                enitiy->hit(3);
            } else {
                if (auto t = dynamic_cast<Tank *>(enitiy)) {
                    if (t->isLaser()) {
                        continue;
                    }
                    enitiy->hit(2);
                }
                return true;
            }
        }
        return false;
    }
}
void Game::complete(bool win) {
    gui.clear();
    gui.printMsg(9, 30, win ? "YOU WIN" : "YOU LOST");
    gui.printMsg(10, 25, "Game ended, score:", score);
    gui.redraw();
    usleep(3000000);
    int c = gui.get();
    if (c == 'q') {
        gui.end();
        exit(0);
    }
    remove_all<Bullet>();
    remove_all<Tank>();
    remove_all<Mine>();
    Tank::init();
    score = 0;
    player->reset();
    player->row = player_ori[0];
    player->col = player_ori[1];
}

template <typename T> list<T *> Game::get_items() {
    auto selected = list<T *>();
    auto ii = items.begin();
    while (ii != items.end()) {
        if (dynamic_cast<T *>(*ii)) {
            selected.push_front(dynamic_cast<T *>(*ii));
        }
        ii++;
    }
    return selected;
}

template <typename T> void Game::remove_all() {
    auto ii = items.begin();
    while (ii != items.end()) {
        if (typeid(**ii) == typeid(T)) {
            (*ii)->queue_delete();
        }
        ii++;
    }
}