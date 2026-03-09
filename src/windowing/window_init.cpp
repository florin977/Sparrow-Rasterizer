#include "sparrow_rasterizer/utils/depth_buffer.hpp"
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
Window::Window()
    : width(1280), height(720), buffer(1280, 720), depth_buffer(1280, 720) {
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

void Window::event_loop() {}

void Window::handle_events(Scene &scene) {
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_EVENT_QUIT:
      stop();
      break;
    case SDL_EVENT_WINDOW_RESIZED:
      SDL_GetWindowSize(window_handle, &width, &height);
      buffer.resize_buffer(width, height);
      depth_buffer.resize_buffer(width, height);
      break;
    case SDL_EVENT_KEY_DOWN:
      handle_keys(scene);
      break;
    }
  }
}

void Window::handle_keys(Scene &scene) {
  switch (event.key.key) {
  case SDLK_ESCAPE:
    stop();
    break;
  case SDLK_W:
    scene.camera.translate_forward(0.1f);
    break;
  case SDLK_S:
    scene.camera.translate_backward(0.1f);
    break;
  case SDLK_A:
    scene.camera.translate_left(0.1f);
    break;
  case SDLK_D:
    scene.camera.translate_right(0.1f);
    break;
  }
}

void Window::render() {
  SDL_UpdateTexture(canvas, NULL, buffer.get_data(), buffer.get_pitch());
  SDL_RenderTexture(renderer, canvas, NULL, NULL);

  SDL_RenderPresent(renderer);
  buffer.clear_buffer(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
  depth_buffer.clear_buffer();
}

bool Window::active() { return is_running; }

void Window::stop() { is_running = false; }
} // namespace sparrow_rasterizer
