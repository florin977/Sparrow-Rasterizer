#include <sparrow_rasterizer/windowing/window_init.hpp>

int main() {
  sparrow_rasterizer::Window raster_window;

  raster_window.event_loop();

  return 0;
}
