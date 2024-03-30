#include "worm.h"
#include "gridsearch.h"

int Worm::id = 0;

Worm::Worm(int x, int y, WormGrid* grid) : body({SDL_Point{x, y}}), _grid(grid) {
  id++;
  _id = id;
  _grid->Add(x, y, this);
}

Worm::Worm(vector<SDL_Point> body, WormGrid* grid) : body(std::move(body)), _grid{grid}, _id(++id) {}

Worm::Worm(Worm &&source) noexcept : body(std::move(source.body)), _grid(source._grid), _id(source._id) {}

Worm& Worm::operator=(Worm &&source) noexcept {
  if (this != &source) {
    body = std::move(source.body);
    _grid = source._grid;
    _id = source._id;
  }
  return *this;
}

/*
 * Getters
 */
XY_Coords Worm::GetHead() const {
  const auto& head = body.back();
  return {head.x, head.y};
}

bool Worm::IsDead() const { return body.empty(); }

bool Worm::IsWormHead(int x, int y) const {
  const auto& head = body.back();
  return x == head.x && y == head.y;
}

int Worm::Id() const { return _id; }

/*
 * Helpers
 */

optional<XY_Coords> Worm::FindNext(SDL_Point& goal) {
  GridSearch grid_search( _grid->MakeSearchGrid());

  return grid_search.FindNext(GetHead(), {goal.x, goal.y});
}

/*
 * Mutations
 */

void Worm::Update(SDL_Point& goal, bool reverse_if_no_next = true) {
  auto next_cell_optional = FindNext(goal);

  if (next_cell_optional.has_value()) {
    SDL_Point next_cell{next_cell_optional.value()};

    _grid->Add(next_cell.x, next_cell.y, this);

    body.push_back(next_cell);

    if (!_growing) {
      auto body_begin{body.begin()};
      _grid->Remove((*body_begin).x, (*body_begin).y);
      // Remove the tail from the vector.
      body.erase(body_begin);
    } else {
      _growing = false;
    }
  } else if (reverse_if_no_next) {
    std::reverse(body);
    Update(goal, false);
  }
}

void Worm::Grow() { _growing = true; }

optional<vector<SDL_Point>> Worm::Bitten(int x, int y) {
  _grid->Remove(x, y);

  auto item = std::find_if(body.begin(), body.end(), [x, y](const auto& item) {
    return item.x == x && item.y == y;
  });

  if (item == body.begin()) {
    body.erase(body.begin());
  } else if (item + 1 == body.end()) {
    body.pop_back();
    if (!body.empty()) {
      std::reverse(body.begin(), body.end());
    }
  } else if (item != body.end()) {
    vector<SDL_Point> new_worm_body{item + 1, body.end()};
    body.erase(item, body.end());
    std::reverse(body);

    return new_worm_body;
  }

  return std::nullopt;
}
