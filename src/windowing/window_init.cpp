#include "sparrow_rasterizer/utils/pixel_buffer.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <glm/ext/vector_float4.hpp>
#include <sparrow_rasterizer/windowing/window_init.hpp>

namespace sparrow_rasterizer {
Window::Window() : width(1280), height(720), buffer(1280, 720) {
  if (SDL_Init(SDL_INIT_VIDEO) == false) {
    SDL_Log("Failed to start SDL Video: %s\n", SDL_GetError());
  }

  window_handle = SDL_CreateWindow("Sparrow Rasterizer", width, height,
                                   SDL_WINDOW_RESIZABLE);
  if (!window_handle) {
    SDL_Log("Could not initialize SDL window: %s\n", SDL_GetError());
  }

  renderer = SDL_CreateRenderer(window_handle, nullptr);
  if (!renderer) {
    SDL_Log("Failed to create renderer: %s\n", SDL_GetError());
  }

  canvas = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                             SDL_TEXTUREACCESS_STREAMING, width, height);
  if (!canvas) {
    SDL_Log("Failed to create canvas: %s\n", SDL_GetError());
  }

  SDL_GetWindowSize(window_handle, &width, &height);
  buffer.resize_buffer(width, height);

  is_running = true;
}

Window::~Window() {
  if (canvas) {
    SDL_DestroyTexture(canvas);
  }
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
    case SDL_EVENT_WINDOW_RESIZED:
      SDL_GetWindowSize(window_handle, &width, &height);
      buffer.resize_buffer(width, height);
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
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      buffer.set_pixel(x, y, glm::vec4{1.0f, 1.0f, 1.0f, 1.0f});
    }
  }
  SDL_UpdateTexture(canvas, NULL, buffer.get_data(), buffer.get_pitch());
  SDL_RenderTexture(renderer, canvas, NULL, NULL);

  SDL_RenderPresent(renderer);
}

bool Window::active() { return is_running; }

void Window::stop() { is_running = false; }
} // namespace sparrow_rasterizer
