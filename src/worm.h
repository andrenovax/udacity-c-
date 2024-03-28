#ifndef WORM_H
#define WORM_H

#include <vector>
#include <array>
#include <optional>

#include "SDL.h"

typedef std::array<int, 2> XY_Coords;

class Worm {
 public:
  Worm(int x, int y);

  Worm(Worm &&source) noexcept;

  // attributes
  std::vector<SDL_Point> body;

  // getters
  bool IsWormCell(int x, int y) const;
  bool IsWormHead(int x, int y) const;
  bool IsDead() const;
  array<int, 2> GetHead() const;

  // mutations
  void Move(int x, int y);
  void Move(const array<int, 2> xy);
  void Grow(int x, int y);
  void Grow(const array<int, 2> xy);

  std::optional<Worm> Bitten(int x, int y);


 private:
  Worm(std::vector<SDL_Point> body) : body(std::move(body)) {}
};

#endif