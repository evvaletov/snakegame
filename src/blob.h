#ifndef BLOB_H
#define BLOB_H

#include <vector>
#include <random>
#include <future>
#include "SDL.h"
#include "character.h"

// FP.2. Classes follow and appropriate inheritance hierarchy.
class Blob : public Character {
public:
    // enum class Direction { kUp, kDown, kLeft, kRight };

    Blob(int grid_width, int grid_height, std::random_device &dev, bool active);

    // FP.3. Derived class functions override virtual base class functions.
    void Update(std::promise<bool> &&prms) override;

    //void GrowBody();

    // FP.3. Derived class functions override virtual base class functions.
    [[nodiscard]] bool CharacterCell(int x, int y) const override;

    // Direction direction = Direction::kUp;

    // float speed{0.1f};
    // int size{1};
    // bool alive{true};
    // float head_x;
    // float head_y;
    // std::vector<SDL_Point> body;
    bool active;

private:
    // FP.3. Derived class functions override virtual base class functions.
    void UpdateHead() override;

    // FP.3. Derived class functions override virtual base class functions.
    void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell) override;

    // std::random_device dev1;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_number;

    // bool growing{false};
    // int grid_width;
    // int grid_height;
};

#endif