#ifndef WORMS_H
#define WORMS_H

#include <unordered_map>

#include "grid2d.h"
#include "worm.h"

class Worms {
 public:
  Worms(int x_length, int y_length);

  // attributes
  std::unordered_map<int, std::unique_ptr<Worm>> items{};

  // Getters
  bool IsEmpty();
  bool IsWormCell(int x, int y);
  int Size();

  // Mutations
  bool UpdatePositionsToTarget(SDL_Point& target);
  void UpdateIfBitten(int bitten_x, int bitten_y);
  void AddWorm(int x, int y);
  void AddWorm(const vector<SDL_Point>& body);

 private:
  Grid2D<Worm*> _grid;
};

#endif