#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include "character.h"

// FP.2. Classes follow and appropriate inheritance hierarchy.
class Snake : public Character {
public:
    // enum class Direction { kUp, kDown, kLeft, kRight };

    Snake(int grid_width, int grid_height) :
            Character(grid_width, grid_height, grid_width / 2, grid_height / 2) {}

    // FP.3. Derived class functions override virtual base class functions.
    void Update(std::promise<bool> &&prms) override;

    void GrowBody();

    // FP.3. Derived class functions override virtual base class functions.
    [[nodiscard]] bool CharacterCell(int x, int y) const override;

    // Direction direction = Direction::kUp;

    // float speed{0.1f};
    // int size{1};
    // bool alive{true};
    // float head_x;
    // float head_y;
    // std::vector<SDL_Point> body;

private:
    // FP.3. Derived class functions override virtual base class functions.
    void UpdateHead() override;

    // FP.3. Derived class functions override virtual base class functions.
    void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell) override;

    bool growing{false};
    // int grid_width;
    // int grid_height;
};

#endif