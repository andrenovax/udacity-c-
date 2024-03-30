#ifndef WORM_GRID_H
#define WORM_GRID_H

#include "grid2d.h"

class WormGrid : public Grid2D<Worm*> {
 public:
  WormGrid(int x_length, int y_length) : Grid2D<Worm*>(x_length, y_length) {}
};

#endif