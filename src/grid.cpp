#include "SDL.h"
#include "grid.h"

#include <vector>
#include <ranges>

using std::vector;

Grid::Grid(int width, int height) {
  for (int row : std::views::iota(0, height)) {
    for (int column : std::views::iota(0, width)) {
      _nodes[row][column] = GridNodeState::kEmpty;
    }
  }
}

// getters
bool Grid::IsEmpty(int x, int y) const {
  return _nodes[x][y] == GridNodeState::kEmpty;
}

int Grid::Width() const { return _nodes.size(); }
int Grid::Height() const { return _nodes[0].size(); }

// mutations

void Grid::AddObstacle(int x, int y) { _nodes[y][x] = GridNodeState::kObstacle; }

void Grid::AddObstacle(SDL_Point &point) {
  _nodes[point.y][point.x] = GridNodeState::kObstacle;
}

void Grid::AddObstacle(vector<SDL_Point> &points) {
  for (auto &point : points) {
    AddObstacle(point);
  }
}

void Grid::ReplaceObstacles(vector<SDL_Point> &old_points,
                      vector<SDL_Point> &new_points) {
  Clear(old_points);
  AddObstacle(new_points);
}

void Grid::Close(int x, int y) { _nodes[y][x] = GridNodeState::kClosed; }

void Grid::Clear(SDL_Point &point) {
  _nodes[point.y][point.x] = GridNodeState::kEmpty;
}

void Grid::Clear(vector<SDL_Point> &points) {
  for (auto &point : points) {
    Clear(point);
  }
}
