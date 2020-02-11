#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include "blob.h"

class Renderer {
public:
    Renderer(const std::size_t screen_width, const std::size_t screen_height,
             const std::size_t grid_width, const std::size_t grid_height);

    ~Renderer();

    void Render(Snake const snake, Blob const blob, SDL_Point const &food);

    void UpdateWindowTitle(float score, int fps);

private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;

    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;

    template<typename T>
    std::string to_string_with_precision(const T a_value, const int n);
};

#endif