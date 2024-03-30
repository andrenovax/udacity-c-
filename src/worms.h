#ifndef WORMS_H
#define WORMS_H

#include <unordered_map>

#include "wormgrid.h"
#include "worm.h"

class Worms {
 public:
  Worms(int x_length, int y_length);

  // attributes
  std::unordered_map<int, std::unique_ptr<Worm>> items{};

  // Getters
  bool IsEmpty();
  bool IsWormCell(int x, int y);

  // Mutations
  void Update(SDL_Point& target);
  void UpdateIfBitten(int bitten_x, int bitten_y);
  void AddWorm(int x, int y);
  void AddWorm(const vector<SDL_Point>& body);

 private:
  WormGrid _grid;

};

#endif