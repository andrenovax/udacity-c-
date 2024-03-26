#ifndef GRID_H
#define GRID_H

#include <vector>
#include <ranges>

#include "SDL.h"

using std::vector;


class Grid {
 public:
  Grid(int width, int height);

  // getters
  bool IsEmpty(int x, int y) const;
  int Width() const;
  int Height() const;

  // mutations
  void AddObstacle(int x, int y);
  void AddObstacle(SDL_Point &point);
  void AddObstacle(vector<SDL_Point> &points);
  void ReplaceObstacles(vector<SDL_Point> &old_points,
                        vector<SDL_Point> &new_points);
  void Close(int x, int y);

 private:
  enum class GridNodeState { kEmpty, kObstacle, kClosed };

  vector<vector<GridNodeState>> _nodes;

  void Clear(SDL_Point &point);
  void Clear(vector<SDL_Point> &points);
};

#endif