#include "SDL.h"
#include "grid.h"

#include <vector>
#include <ranges>

using std::abs;
using std::vector;

Grid::Grid(int width, int height) : _nodes(height) {
  for (int y = 0; y < height; ++y) {
    _nodes[y].reserve(width);
    for (int x = 0; x < width; ++x) {
      _nodes[y].emplace_back(x, y);
    }
  }
}

Grid::Grid(const Grid &source) : _nodes(source.Height()) {
  auto width = source.Width();
  for (int y = 0; y < source.Height(); ++y) {
    _nodes[y].reserve(width);
    for (int x = 0; x < width; ++x) {
      auto source_node{source.GetNode(x, y)};
      _nodes[y].emplace_back(x, y, source_node->state);
      _nodes[y][x].g = source_node->g;
      _nodes[y][x].h = source_node->h;
    }
  }

  for (int y = 0; y < source.Height(); ++y) {
    for (int x = 0; x < width; ++x) {
      auto source_node_parent{source.GetNode(x, y)->parent};
      if (source_node_parent != nullptr) {
        _nodes[y][x].parent = GetNode(source_node_parent->x, source_node_parent->y);
      }
    }
  }
}

Grid& Grid::operator=(const Grid &source) {
  if (this == &source) {
    return *this;
  }

  _nodes.clear();
  _nodes.resize(source.Height());

  for (int y = 0; y < source.Height(); ++y) {
    _nodes[y].clear();
    for (int x = 0; x < source.Width(); ++x) {
      _nodes[y].emplace_back(x, y, source.GetNode(x, y)->state);
      _nodes[y][x].g = source_node->g;
      _nodes[y][x].h = source_node->h;
    }
  }

  for (int y = 0; y < source.Height(); ++y) {
    for (int x = 0; x < width; ++x) {
      auto source_node_parent{source.GetNode(x, y)->parent};
      if (source_node_parent != nullptr) {
        _nodes[y][x].parent = GetNode(source_node_parent->x, source_node_parent->y);
      }
    }
  }

  return *this;
}

/*
 * Getters
*/

Grid::Node* Grid::GetNode(int x, int y) {
  return &(_nodes[y][x]);
}

Grid::Node* Grid::GetNode(SDL_Point &point) {
  return GetNode(point.x, point.y);
}

Grid::Node* Grid::GetNeighbourNode(Node &node, int neighbour) {
  int x2 = node.x + NODE_NEIGHBOUR_DELTA[neighbour][0];
  int y2 = node.y + NODE_NEIGHBOUR_DELTA[neighbour][1];

  if (x2 == Width()) {
    x2 = 0;
  } else if (x2 < 0) {
    x2 = Width() - 1;
  }

  if (y2 == Height()) {
    y2 = 0;
  } else if (y2 < 0) {
    y2 = Height() - 1;
  }

  return GetNode(x2, y2);
}

std::vector<Grid::Node*> Grid::GetNeighbourNodes(Grid::Node &node) {
  std::vector<Grid::Node*> nodes{};

  for (int neighbour = 0; neighbour < 4; neighbour++) {
    auto neighbour_node {GetNeighbourNode(node, neighbour)};
    nodes.push_back(neighbour_node);
  }

  return nodes;
}

bool Grid::IsEmpty(int x, int y) {
  return GetNode(x, y)->IsEmpty();
}

int Grid::Width() const { return _nodes.size(); }

int Grid::Height() const { return _nodes[0].size(); }

/*
 * Mutations
*/

void Grid::AddObstacle(int x, int y) {
  GetNode(x, y)->state = Node::State::kObstacle;
}

void Grid::AddObstacle(SDL_Point &point) {
  GetNode(point)->state = Node::State::kObstacle;
}

void Grid::AddObstacle(vector<SDL_Point> &points) {
  for (auto &point : points) {
    AddObstacle(point);
  }
}

void Grid::Reset(SDL_Point &point) {
  auto node = GetNode(point);
  node->g = 0;
  node->h = std::numeric_limits<int>::max();
  node->state = Node::State::kEmpty;
  node->parent = nullptr;
}

void Grid::Reset(vector<SDL_Point> &points) {
  for (auto &point : points) {
    Reset(point);
  }
}

void Grid::ReplaceObstacles(vector<SDL_Point> &old_points,
                            vector<SDL_Point> &new_points) {
  Reset(old_points);
  AddObstacle(new_points);
}

/**
 * Grid::Node
 */

int Grid::Node::FValue() const {
  return g + h;
}

bool Grid::Node::operator>(Node const& node) const {
  return FValue() > node.FValue();
}

bool Grid::Node::operator<(Node const& node) const {
  return FValue() < node.FValue();
}

bool Grid::Node::IsEmpty() const {
  return state == Grid::Node::State::kEmpty;
}

int Grid::Node::Distance(Node* node) const {
  return abs(x - node->x) + abs(y - node->y);
}
