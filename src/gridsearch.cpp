#include "gridsearch.h"

#include <algorithm>
#include <string>
#include <vector>

using std::abs;
using std::sort;
using std::vector;

/**
 * Compare the F values of two cells.
 */
bool GridSearch::Compare(const Node &a, const Node &b) {
  return (a.g + a.h) > (b.g + b.h);
}

/**
 * Sort the two-dimensional vector of ints in descending order
 */
void GridSearch::CellSort(Nodes *v)  {
  sort(v->begin(), v->end(), Compare);
}

// Calculate the manhattan distance
int GridSearch::Heuristic(int x1, int y1, int x2, int y2) {
  return abs(x2 - x1) + abs(y2 - y1);
}

/**
 * Expand current nodes neighbors and add them to the open list.
 */
void GridSearch::ExpandNeighbors(Node* current, int goal[2], Nodes &openlist) {
  // Loop through current node's potential neighbors.
  for (int i = 0; i < 4; i++) {
    int x2 = current->x + NODE_NEIGHBOUR_DELTA[i][0];
    int y2 = current->y + NODE_NEIGHBOUR_DELTA[i][1];

    if (x2 == _grid.Width()) {
      x2 = 0;
    } else if (x2 < 0) {
      x2 = _grid.Width() - 1;
    }

    if (y2 == _grid.Height()) {
      y2 = 0;
    } else if (y2 < 0) {
      y2 = _grid.Height() - 1;
    }

    if (_grid.IsEmpty(x2, y2)) {
      int g2 = current->g + 1;
      int h2 = Heuristic(x2, y2, goal[0], goal[1]);
      openlist.push_back({x2, y2, g2, h2, current});
      _grid.Close(x2, y2);
    }
  }
}

std::vector<GridSearch::Node> GridSearch::MakePath(Node &current_node, Node &start_node) {
  Nodes path_found{current_node};

  Node *current = &current_node;
  while (current != &start_node) {
    auto parent = current_node.parent;
    path_found.push_back(*parent);
    current = parent;
  }

  std::reverse(path_found.begin(), path_found.end());

  return path_found;
}

std::optional<GridSearch::Nodes> GridSearch::AStarSearch(std::array<int, 2> init,
                                                         int goal[2]) {
  int x = init[0];
  int y = init[1];
  int g = 0;
  int h = Heuristic(x, y, goal[0], goal[1]);

  Node start_node{x, y, g, h};
  Nodes open{start_node};

  while (open.size() > 0) {
    // Get the next node
    CellSort(&open);
    auto current = open.back();
    open.pop_back();

    if (current.x == goal[0] && current.y == goal[1]) {
      return MakePath(current, start_node);
    }

    ExpandNeighbors(&current, goal, open);
  }
}

std::optional<std::array<int, 2>> GridSearch::FindNext(std::array<int, 2> init, int goal[2]) {
  auto path = AStarSearch(init, goal);
  if (path.has_value()) {
    auto path_value = path.value();
    if (path_value.size() > 1) {
      auto next_node = path_value[1];
      return std::optional<std::array<int, 2>>{{next_node.x, next_node.y}};
    }
  }
}
