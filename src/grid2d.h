#ifndef GRID_2D_H
#define GRID_2D_H

#include <optional>
#include <vector>

using std::optional;
using std::vector;

template <typename T>
struct Grid2D {
  vector<vector<optional<T>>> _items;

  Grid2D(int x_length, int y_length)
      : _items(y_length, vector<optional<T>>(x_length)) {}

  // Getters
  optional<T> Get(int x, int y) const { return _items[y][x]; };

  bool HasValue(int x, int y) { return Get(x, y).has_value(); }

  // Mutations
  void Add(int x, int y, T item) { _items[y][x] = item; };

  void Remove(int x, int y) {
    _items[y][x] = std::nullopt;
  };
};

#endif