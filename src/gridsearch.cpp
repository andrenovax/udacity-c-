#include "gridsearch.h"

#include <algorithm>
#include <string>

using std::sort;
using std::array;
using std::optional;

void GridSearch::ExpandNeighbors(Grid::Node *current, Grid::Node *end_node, Nodes &openlist) {
  auto neighbours = _grid.GetNeighbourNodes(*current);
  for (auto &neighbour : neighbours) {
    if (neighbour->IsEmpty()) {
      neighbour->g = current->g + 1;
      neighbour->h = neighbour->Distance(end_node);
      neighbour->parent = current;
      neighbour->state = Grid::Node::State::kPath;
      openlist.push_back(neighbour);
    }
  }
}

GridSearch::Nodes GridSearch::MakePath(Grid::Node *current_node, Grid::Node *start_node) {
  Nodes path_found{current_node};

  Grid::Node *current = current_node;

  while (current != start_node) {
    auto parent = current_node->parent;
    path_found.push_back(parent);
    current = parent;
  }

  std::reverse(path_found.begin(), path_found.end());

  return path_found;
}

optional<GridSearch::Nodes> GridSearch::AStarSearch(XY_Coords init, XY_Coords goal) {
  auto end_node{_grid.GetNode(goal[0], goal[1])};
  auto start_node{_grid.GetNode(init[0], init[1])};
  start_node->g = 0;
  start_node->h = start_node->Distance(end_node);

  Nodes open{start_node};

  while (open.size() > 0) {
    // Get the next node
    sort(open.begin(), open.end());
    auto next_node = open.back();
    open.pop_back();

    if (next_node == end_node) {
      return MakePath(next_node, start_node);
    }

    ExpandNeighbors(next_node, end_node, open);
  }
}

optional<GridSearch::XY_Coords> GridSearch::FindNext(XY_Coords init, XY_Coords goal) {
  auto path = AStarSearch(init, goal);
  if (path.has_value()) {
    auto path_value = path.value();
    if (path_value.size() > 1) {
      auto next_node = path_value[1];
      return optional<XY_Coords>{{next_node->x, next_node->y}};
    }
  }
}
