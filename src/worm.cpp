#include "worm.h"
#include <algorithm>
#include "gridsearch.h"
#include <cmath>

int Worm::id = 0;

Worm::Worm(int x, int y, Grid2D<Worm*>* grid)
    : body({SDL_Point{x, y}}), _grid(grid) {
  id++;
  _id = id;
  _grid->Add(x, y, this);
}

Worm::Worm(vector<SDL_Point> body, Grid2D<Worm*>* grid)
    : body(std::move(body)), _grid{grid}, _id(++id) {}

Worm::Worm(Worm&& source) noexcept
    : body(std::move(source.body)), _grid(source._grid), _id(source._id) {}

Worm& Worm::operator=(Worm&& source) noexcept {
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

Grid MakeSearchNodes(Grid2D<Worm*>* _grid) {
  auto& items = _grid->_items;
  vector<vector<Grid::Node>> nodes(items.size(),
                                   vector<Grid::Node>(items[0].size()));

  for (int y = 0; y < items.size(); ++y) {
    for (int x = 0; x < items[0].size(); ++x) {
      auto state = items[y][x].has_value() ? Grid::Node::State::kObstacle
                                           : Grid::Node::State::kEmpty;
      nodes[y][x] = Grid::Node(x, y, state);
    }
  }

  return Grid(nodes);
}

optional<XY_Coords> Worm::FindNext(SDL_Point& goal) {
  Grid temp_grid = MakeSearchNodes(_grid);
  GridSearch grid_search(temp_grid);

  return grid_search.FindNext(GetHead(), {goal.x, goal.y});
}

/*
 * Mutations
 */

void Worm::Update(SDL_Point& goal, std::shared_ptr<std::atomic<bool>> has_reached_goal) {
  cells_to_move += speed;
  int number_of_steps = std::floor(cells_to_move);
  if (number_of_steps == 0) {
    return;
  }

  cells_to_move -= number_of_steps;

  for (int i = 0; i < number_of_steps; ++i) {
    if (has_reached_goal->load()) {
      return;
    }
    auto next_cell_optional = FindNext(goal);

    if (!next_cell_optional.has_value()) {
      std::reverse(body.begin(), body.end());
      next_cell_optional = FindNext(goal);
    }

    if (next_cell_optional.has_value()) {
      auto& val{next_cell_optional.value()};
      SDL_Point next_cell{val[0], val[1]};

      _grid->Add(next_cell.x, next_cell.y, this);

      body.push_back(next_cell);

      if (!_growing) {
        auto body_begin{body.begin()};
        _grid->Remove(body_begin->x, body_begin->y);
        // Remove the tail from the vector.
        body.erase(body_begin);
      } else {
        _growing = false;
      }
      // high speed eating mode
      if (IsWormHead(goal.x, goal.y)) {
        if (!has_reached_goal->load()) {
          has_reached_goal->store(true);
          Grow();
          speed += 0.01;
        }
        return;
      }
    }
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
    std::reverse(body.begin(), body.end());

    return new_worm_body;
  }

  return std::nullopt;
}
