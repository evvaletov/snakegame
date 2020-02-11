#include "renderer.h"
#include <iostream>
#include <string>
#include <sstream>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
        : screen_width(screen_width),
          screen_height(screen_height),
          grid_width(grid_width),
          grid_height(grid_height) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create Window
    sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, screen_width,
                                  screen_height, SDL_WINDOW_SHOWN);

    if (nullptr == sdl_window) {
        std::cerr << "Window could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create renderer
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == sdl_renderer) {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
}

Renderer::~Renderer() {
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

void Renderer::Render(Snake const snake, Blob const blob, SDL_Point const &food) {
    SDL_Rect block;
    block.w = screen_width / grid_width;
    block.h = screen_height / grid_height;

    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Render food
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    block.x = food.x * block.w;
    block.y = food.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);

    if (blob.active) {
        // Render blob's body
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x80, 0x00, 0xFF);
        for (SDL_Point const &point : blob.body) {
            block.x = point.x * block.w;
            block.y = point.y * block.h;
            SDL_RenderFillRect(sdl_renderer, &block);
        }

        // Render blob's head
        block.x = static_cast<int>(blob.head_x) * block.w;
        block.y = static_cast<int>(blob.head_y) * block.h;
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFA, 0x9A, 0xFF);
        SDL_RenderFillRect(sdl_renderer, &block);
    }

    // Render snake's body
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    for (SDL_Point const &point : snake.body) {
        block.x = point.x * block.w;
        block.y = point.y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
    }

    // Render snake's head
    block.x = static_cast<int>(snake.head_x) * block.w;
    block.y = static_cast<int>(snake.head_y) * block.h;
    if (snake.alive) {
        if (blob.active and blob.CharacterCell(snake.head_x, snake.head_y)) {
            SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0xFF, 0xFF);
        } else {
            SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
        }
    } else {
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    }
    SDL_RenderFillRect(sdl_renderer, &block);

    // Update Screen
    SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(float score, int fps) {
    std::string title{"Snake Score: " + to_string_with_precision<float>(score, 2) + " FPS: " + std::to_string(fps)};
    SDL_SetWindowTitle(sdl_window, title.c_str());
}

// FP.4. Templates generalize functions in the project.
template<typename T>
std::string Renderer::to_string_with_precision(const T a_value, const int n)
// This function was obtained from  URL: https://stackoverflow.com/questions/16605967/set-precision-of-stdto-string-when-converting-floating-point-values
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}