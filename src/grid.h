#ifndef GRID_H
#define GRID_H

#include <vector>
#include <ranges>

#include "SDL.h"

using std::vector;


class Grid {
 public:
  struct Node {
    enum class State { kEmpty, kObstacle, kPath };

    int x, y, g = 0, h = std::numeric_limits<int>::max();

    State state = State::kEmpty;
    Node* parent = nullptr;

    Node(int x, int y): x{x}, y{y} {}

    bool operator>(Node const& node) const;
    bool operator<(Node const& node) const;

    bool IsEmpty() const;
    int Distance(Node* node) const;
    int FValue() const;
  };


  Grid(int width, int height);

  // Getters
  bool IsEmpty(int x, int y);

  Node* GetNode(int x, int y);
  Node* GetNode(SDL_Point &point);
  Node* GetNeighbourNode(Node &node, int neighbour);
  std::vector<Grid::Node*> GetNeighbourNodes(Grid::Node &node);

  // Setters
  void AddObstacle(int x, int y);
  void AddObstacle(SDL_Point &point);
  void AddObstacle(vector<SDL_Point> &points);

  void ReplaceObstacles(vector<SDL_Point> &old_points,
                        vector<SDL_Point> &new_points);

 private:
  vector<vector<Node>> _nodes;

  static constexpr int NODE_NEIGHBOUR_DELTA[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

  // Getters
  int Width() const;
  int Height() const;

  // Setters
  void Reset(SDL_Point &point);
  void Reset(vector<SDL_Point> &points);
};

#endif