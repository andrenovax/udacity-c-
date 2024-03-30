#ifndef WORM_GRID_H
#define WORM_GRID_H

#include "grid2d.h"
#include "grid.h"

class WormGrid : Grid2D<Worm*> {
 public:
  WormGrid(int x_length, int y_length) : Grid2D<Worm*>(x_length, y_length) {}

  vector<vector<Grid::Node>> MakeSearchGrid() {
    vector<vector<Grid::Node>> nodes(_items.size(), vector<Grid::Node>(_items[0].size()));

    for (int y = 0; y < _items.size(); ++y) {
      for (int x = 0; x < _items[0].size(); ++x) {
        auto state = _items[y][x].has_value() ? Grid::Node::State::kObstacle : Grid::Node::State::kEmpty;
        nodes[y][x] = Grid::Node(x, y, state);
      }
    }

    return nodes;
  }
};

#endif