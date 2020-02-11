#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include <random>
#include <future>
#include "SDL.h"

class Character {
public:
    enum class Direction {
        kUp, kDown, kLeft, kRight
    };

    Character(int grid_width, int grid_height, float head_x, float head_y) :
            grid_width(grid_width), grid_height(grid_height), head_x(head_x), head_y(head_y) {}

    Character(int grid_width, int grid_height, std::random_device &dev);

    virtual void Update(std::promise<bool> &&prms) = 0;

    // virtual void GrowBody() = 0;
    virtual bool CharacterCell(int x, int y) const = 0;

    Direction direction = Direction::kUp;

    float speed{0.1f};
    int size{1};
    bool alive{true};
    float head_x;
    float head_y;
    std::vector<SDL_Point> body;

protected:
    virtual void UpdateHead() = 0;

    virtual void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell) = 0;

    SDL_Point WrappedXY(int x, int y);

    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;
    std::uniform_int_distribution<int> random_direction;

    //bool growing{false};
    int grid_width;
    int grid_height;
};

#endif