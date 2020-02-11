#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
    constexpr std::size_t kFramesPerSecond{60};
    constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
    constexpr std::size_t kScreenWidth{640};
    constexpr std::size_t kScreenHeight{640};
    constexpr std::size_t kGridWidth{32};
    constexpr std::size_t kGridHeight{32};

    // FP.1. The project accepts user input and processes the input.
    bool blob_active;
    int input = 2;
    while (input != 0 and input != 1) {
        std::cout << "Play game with blob active? [1 = YES / 0 = NO] ";
        std::cin >> input;
    }

    blob_active = input == 1;

    Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
    Controller controller;
    Game game(kGridWidth, kGridHeight, blob_active);
    game.Run(controller, renderer, kMsPerFrame);
    std::cout << "Game has terminated successfully!\n";
    std::cout << "Score: " << game.GetScore() << "\n";
    std::cout << "Size: " << game.GetSize() << "\n";
    return 0;
}