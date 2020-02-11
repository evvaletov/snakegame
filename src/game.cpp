#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, bool blob_active)
    : snake(grid_width, grid_height), blob(grid_width, grid_height, dev, blob_active),
      engine(dev()),
      // Corrected bug where food is occasionally places outside of the game board
      random_w(0, static_cast<int>(grid_width)-1),
      random_h(0, static_cast<int>(grid_height)-1) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, blob, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.CharacterCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  // In case of more than two characters a vector can be used to store the promises and futures, but with only
  // two characters, the snake and the blob, it is probably more efficient to use separate variables as follows.
  // FP.6. A promise and a future are used in the project.
  std::promise<bool> prms_snake;
  std::future<bool> ftr_snake = prms_snake.get_future();
  std::promise<bool> prms_blob;
  std::future<bool> ftr_blob = prms_blob.get_future();

  // FP.5. The project uses multithreading.
  std::thread t_snake(&Snake::Update, &snake, std::move(prms_snake));
  std::thread t_blob(&Blob::Update, &blob, std::move(prms_blob));

  // FP.6. A promise and a future are used in the project.
  ftr_snake.wait();
  ftr_blob.wait();

  t_snake.join();
  t_blob.join();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }

  // Check if snake's head is in the blob
  if (blob.active and blob.CharacterCell(snake.head_x, snake.head_y)) {
      // Decrease the score by 0.01
      score-=0.01;
  }
}

float Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }