#ifndef _BITGRID_H_
#define _BITGRID_H_
#include "Constants.h"
#include <bitset>
#include <iostream>
#include <vector>

class BitGrid {
  private:
    std::vector<uint32_t> grid;
    int rows, cols;

  public:
    BitGrid(int rows, int cols) : rows(rows), cols(cols) {
        int elementsPerRow = (cols + 31) / 32;
        grid.resize(rows * elementsPerRow, 0);
    }

    void set(int row, int col, bool value) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw std::out_of_range("Row or column out of range");
        }
        int index = row * ((cols + 31) / 32) + col / 32;
        int bit = col % 32;
        if (value) {
            grid[index] |= (1 << bit);
        } else {
            grid[index] &= ~(1 << bit);
        }
    }

    bool get(int row, int col) const {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw std::out_of_range("Row or column out of range");
        }
        int index = row * ((cols + 31) / 32) + col / 32;
        int bit = col % 32;
        return (grid[index] >> bit) & 1;
    }

    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << get(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }
};

#endif