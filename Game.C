#include "Bomb.h"
#include "Bullet.h"
#include "Game.h"
#include "LivingEntity.h"
#include "Mine.h"
#include "Player.h"
#include "Tank.h"
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <curses.h>
#include <math.h>
#include <memory>
#include <unistd.h>
Game::Game() {
    Tank::init();
    gui.init();
    player = new Player(this);
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

void Game::update() {
    gui.clear();
    gui.printMsg(2, 68, "Bullet", player->bullet_count);
    gui.printMsg(3, 68, "Score", score);
    auto tank_num_left = Tank::get_num_left();
    gui.printMsg(4, 68, "Tank Left", tank_num_left);
    if (get_items<Tank>().size() < 4 && tank_num_left > 0) {
        int row = rand() % (MAX_ROW - MIN_ROW - 10) + 5;
        int col = rand() % (MAX_COL - MIN_COL - 20) + 10;
        items.push_back(new Tank(this, row, col, true));
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
}

bool Game::query_hit(Bullet *bullet) {
    for (auto enitiy : get_items<LivingEntity>()) {
        int width = strcmp(enitiy->get_type(), "Player") == 0 ? 1 : 2;
        if (bullet->row == enitiy->row &&
            abs((int)bullet->col - (int)enitiy->col) < width) {
            if (strcmp(bullet->damageSource, "Player") == 0)
                score += 100;
            enitiy->hit(1);
            return true;
        }
    }
    return false;
}

void Game::complete() {
    gui.clear();
    gui.printMsg(10, 25, "Game ended, score:", score);
    usleep(3000000);
    int c = gui.get();
    if (c == 'q') {
        gui.end();
        exit(0);
    }
    remove_all<Bullet>();
    remove_all<Tank>();
    remove_all<Mine>();

    score = 0;
    player->reset();
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