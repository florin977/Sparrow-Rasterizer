#include "sparrow_rasterizer/windowing/window_init.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

namespace sparrow_rasterizer {
Window::Window() {
  if (SDL_Init(SDL_INIT_VIDEO) == false) {
    SDL_Log("Failed to start SDL Video: %s\n", SDL_GetError());
  }

  window_handle =
      SDL_CreateWindow("Sparrow Rasterizer", 1280, 720, SDL_WINDOW_RESIZABLE);
  if (!window_handle) {
    SDL_Log("Could not initialize SDL window: %s\n", SDL_GetError());
  }

  renderer = SDL_CreateRenderer(window_handle, nullptr);
  if (!renderer) {
    SDL_Log("Failed to create renderer: %s\n", SDL_GetError());
  }

  is_running = true;
}

Window::~Window() {
  if (renderer) {
    SDL_DestroyRenderer(renderer);
  }
  if (window_handle && SDL_WasInit(SDL_INIT_VIDEO)) {
    SDL_DestroyWindow(window_handle);
  }
}

void Window::event_loop() {
  while (active()) {
    handle_events();
    render();
  }
}

void Window::handle_events() {
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_EVENT_QUIT:
      stop();
      break;
    case SDL_EVENT_KEY_DOWN:
      handle_keys();
      break;
    }
  }
}

void Window::handle_keys() {
  switch (event.key.key) {
  case SDLK_ESCAPE:
    stop();
    break;
  }
}

void Window::render() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // TODO: Implement the rasterizer and draw the pixel buffer here

  SDL_RenderPresent(renderer);
}

bool Window::active() { return is_running; }

void Window::stop() { is_running = false; }
} // namespace sparrow_rasterizer
