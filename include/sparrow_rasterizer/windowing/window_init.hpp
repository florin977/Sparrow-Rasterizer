#pragma once

#include "sparrow_rasterizer/utils/pixel_buffer.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

namespace sparrow_rasterizer {
class Window {
private:
  SDL_Renderer *renderer;
  SDL_Texture *canvas;
  bool is_running;

public:
  int width;
  int height;
  Buffer buffer;
  SDL_Window *window_handle;
  SDL_Event event;

  Window();
  ~Window();
  void event_loop();
  void handle_events();
  void handle_keys();
  void render();
  bool active();
  void stop();
};
} // namespace sparrow_rasterizer
