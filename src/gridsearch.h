#ifndef GRIDSEARCH_H
#define GRIDSEARCH_H

#include <vector>
#include <array>
#include <optional>

#include "grid.h"

using std::vector;
using std::array;
using std::optional;

class GridSearch {
 public:
  typedef vector<Grid::Node*> Nodes;
  typedef array<int, 2> XY_Coords;

  GridSearch(Grid& grid);

  optional<XY_Coords> FindNext(XY_Coords init, XY_Coords goal);
  optional<Nodes> AStarSearch(XY_Coords init, XY_Coords goal);

 private:
  Grid& _grid;

  static Nodes MakePath(Grid::Node *current_node, Grid::Node *start_node);

  void ExpandNeighbors(Grid::Node *current,  Grid::Node *end_node, Nodes &openlist);
};

#endif