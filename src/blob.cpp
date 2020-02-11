#include "blob.h"
#include <cmath>
#include <iostream>
#include <future>

Blob::Blob(int grid_width, int grid_height, std::random_device &dev, bool active) : active(active),
                                                                                    engine(dev()), random_number(0, 9),
                                                                                    Character(grid_width, grid_height,
                                                                                              dev) {}

void Blob::Update(std::promise<bool> &&prms) {
    SDL_Point prev_cell{
            static_cast<int>(head_x),
            static_cast<int>(
                    head_y)};  // We first capture the head's cell before updating.
    UpdateHead();
    SDL_Point current_cell{
            static_cast<int>(head_x),
            static_cast<int>(head_y)};  // Capture the head's cell after updating.

    // Update all of the body vector items if the blob head has moved to a new
    // cell.
    if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
        UpdateBody(current_cell, prev_cell);
    }
    prms.set_value(true);
}

void Blob::UpdateHead() {

    // 10% probability of changing direction
    if (random_number(engine) == 0) direction = (Direction) random_direction(engine);

    switch (direction) {
        case Direction::kUp:
            head_y -= speed;
            break;

        case Direction::kDown:
            head_y += speed;
            break;

        case Direction::kLeft:
            head_x -= speed;
            break;

        case Direction::kRight:
            head_x += speed;
            break;
    }

    // Wrap the blob around to the beginning if going off of the screen.
    head_x = fmod(head_x + grid_width, grid_width);
    head_y = fmod(head_y + grid_height, grid_height);
}

void Blob::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
    body.clear();

    for (int dx = -1; dx < 2; dx++) {
        for (int dy = -1; dy < 2; dy++) {
            if (dx != 0 or dy != 0) {
                body.push_back(WrappedXY(current_head_cell.x + dx, current_head_cell.y + dy));
            }
        }
    }
}

// Inefficient method to check if cell is occupied by snake.
bool Blob::CharacterCell(int x, int y) const {
    if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
        return true;
    }
    for (auto const &item : body) {
        if (x == item.x && y == item.y) {
            return true;
        }
    }
    return false;
}