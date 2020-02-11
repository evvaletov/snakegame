#include "character.h"
#include <cmath>
#include <iostream>

Character::Character(int grid_width, int grid_height, std::random_device &dev) : engine(dev()),
                                                                                 grid_width(grid_width),
                                                                                 grid_height(grid_height),
                                                                                 random_direction(0, 3),
                                                                                 random_w(0,
                                                                                          static_cast<int>(grid_width) -
                                                                                          1),
                                                                                 random_h(0,
                                                                                          static_cast<int>(grid_height) -
                                                                                          1) {
    head_x = random_w(engine);
    head_y = random_h(engine);
    direction = (Direction) random_direction(engine);
}

SDL_Point Character::WrappedXY(int x, int y) {
    return SDL_Point({static_cast<int>(fmod(x + grid_width, grid_width)),
                      static_cast<int>(fmod(y + grid_height, grid_height))});
}