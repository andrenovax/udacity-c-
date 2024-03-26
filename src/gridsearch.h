#ifndef GRIDSEARCH_H
#define GRIDSEARCH_H

#include <vector>
#include <array>

#include "grid.h"

using std::abs;
using std::sort;
using std::vector;
using std::array;

class GridSearch {
 public:
  struct Node {
    int x, y, g, h;
    Node* parent;

    Node(int x, int y, int g, int h, Node *parent = nullptr)
        : x{x}, y{y}, g{g}, h{h}, parent{parent} {}
  };

  typedef vector<Node> Nodes;

  // copy grid, so we can modify grid here without affecting the main one
  GridSearch(Grid grid) : _grid{grid} {};

  std::optional<std::array<int, 2>> FindNext(std::array<int, 2> init, int goal[2]);
  std::optional<Nodes> AStarSearch(std::array<int, 2> init, int goal[2]);

 private:
  Grid _grid;

  static constexpr int NODE_NEIGHBOUR_DELTA[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
  static bool Compare(const Node &a, const Node &b);
  static void CellSort(Nodes *v);
  static int Heuristic(int x1, int y1, int x2, int y2);

  static vector<Node> MakePath(Node &current_node, Node &start_node);

  void ExpandNeighbors(Node* current, int goal[2], Nodes &openlist);
};

#endif