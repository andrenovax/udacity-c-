#include "worm.h"


Worm::Worm(int x, int y) : body({SDL_Point{x, y}}) {}

Worm::Worm(Worm &&source) noexcept : body(std::move(source.body)) {}

Worm& Worm::operator=(Worm &&source) noexcept {
  if (this != &source) {
    body = std::move(source.body);
  }
  return *this;
}

/*
 * Getters
 */
XY_Coords Worm::GetHead() const {
  auto head = body.back();
  return {head.x, head.y};
}

bool Worm::IsDead() const { return body.empty(); }

bool Worm::IsWormCell(int x, int y) const {
  for (auto const& item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

bool Worm::IsWormHead(int x, int y) const {
  const auto& head = body.back();
  return x == head.x && y == head.y;
}

/*
 * Mutations
 */
void Worm::Grow(int x, int y) {
  SDL_Point next_cell{x, y};
  body.push_back(next_cell);
}

void Worm::Grow(const XY_Coords &xy) {
  Grow(xy[0], xy[1]);
}

void Worm::Move(int x, int y) {
  SDL_Point next_cell{x, y};
  body.push_back(next_cell);
  body.erase(body.begin());
}

void Worm::Move(const XY_Coords &xy) {
  Move(xy[0], xy[1]);
}

std::optional<Worm> Worm::Bitten(int x, int y) {
  auto item = std::find_if(body.begin(), body.end(), [x, y](const auto& item) {
    return item.x == x && item.y == y;
  });

  if (item == body.begin()) {
    body.erase(body.begin());
    if (!body.empty()) {
      std::reverse(body.begin(), body.end());
    }
  } else if (item + 1 == body.end()) {
    body.pop_back();
  } else if (item != body.end()) {
    std::vector<SDL_Point> new_worm_body;
    new_worm_body.reserve(std::distance(body.begin(), item));

    // Copy the elements in reverse order.
    std::for_each(std::make_reverse_iterator(item),
                  std::make_reverse_iterator(body.begin()),
                  [&new_worm_body](const SDL_Point& point) {
                    new_worm_body.push_back(point);
                  });


    Worm new_worm(std::move(new_worm_body));

    // remove body before the kicked item
    body.erase(body.begin(), item + 1);

    return new_worm;
  }

  return std::nullopt;
}
