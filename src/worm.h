#ifndef WORM_H
#define WORM_H

#include <array>
#include <optional>
#include <vector>

#include "SDL.h"
#include "grid2d.h"

using std::optional;
using std::vector;

typedef std::array<int, 2> XY_Coords;

class Worm {
 public:
  Worm(int x, int y, Grid2D<Worm*>* grid);
  Worm(vector<SDL_Point> body, Grid2D<Worm*>* grid);

  Worm(Worm&& source) noexcept;
  Worm& operator=(Worm&& source) noexcept;

  // attributes
  float speed{0.1};
  vector<SDL_Point> body;

  // getters
  int Id() const;
  bool IsWormHead(int x, int y) const;
  bool IsDead() const;
  XY_Coords GetHead() const;

  // mutations
  void Grow();
  void Update(SDL_Point& goal, std::shared_ptr<std::atomic<bool>> has_reached_goal);

  optional<vector<SDL_Point>> Bitten(int x, int y);

  optional<XY_Coords> FindNext(SDL_Point& goal);

 private:
  static int id;
  float cells_to_move{0};

  // attributes
  int _id;
  Grid2D<Worm*>* _grid;
  bool _growing = false;
};

#endif