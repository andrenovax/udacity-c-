#include "worms.h"

Worms::Worms(int x_length, int y_length) : _grid(x_length, y_length) {}

/*
 * Getters
 * */

bool Worms::IsEmpty() {
  return items.empty();
}

bool Worms::IsWormCell(int x, int y) {
  return _grid.HasValue(x, y);
}

/*
 * Mutations
 * */

void Worms::Update(SDL_Point& target) {
  for (auto &[id, worm] : items) {
    worm->Update(target);
  }
}

void Worms::UpdateIfBitten(int x, int y) {
  auto worm_optional = _grid.Get(x, y);
  if (worm_optional.has_value()) {
    auto worm = worm_optional.value();
    auto new_worm_body = worm->Bitten(x, y);
    if (new_worm_body.has_value()) {
      AddWorm(new_worm_body.value());
    }
    if (worm->isDead()) {
      items.erase(worm->Id());
    }
  }
}

void Worms::AddWorm(int x, int y) {
  auto worm = std::make_unique<Worm>(x, y, _grid);
  items[worm->Id()] = std::move(worm);
}

void Worms::AddWorm(const vector<SDL_Point>& body) {
  auto worm = std::make_unique<Worm>(body, _grid);
  items[worm->Id()] = std::move(worm);
}
