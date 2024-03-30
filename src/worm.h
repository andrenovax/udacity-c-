#ifndef WORM_H
#define WORM_H

#include <array>
#include <optional>
#include <vector>

#include "SDL.h"
#include "grid2d.h"
#include "wormgrid.h"

using std::optional;
using std::vector;

typedef std::array<int, 2> XY_Coords;

class Worm {
 public:
  Worm(int x, int y, WormGrid* grid);
  Worm(vector<SDL_Point> body, WormGrid* grid);

  Worm(Worm &&source) noexcept;
  Worm& operator=(Worm &&source) noexcept;

  // attributes
  vector<SDL_Point> body;

  // getters
  int Id() const;
  bool IsWormHead(int x, int y) const;
  bool IsDead() const;
  XY_Coords GetHead() const;

  // mutations
  void Grow();
  void Update(SDL_Point& goal);

  optional<vector<SDL_Point>> Bitten(int x, int y);

  optional<XY_Coords> FindNext(SDL_Point& goal);

 private:
  static int id;

  // attributes
  int _id;
  WormGrid* _grid;
  bool _growing = false;
};

#endif