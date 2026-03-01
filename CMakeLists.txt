cmake_minimum_required(VERSION 4.2)
project (Sparrow_Rasterizer LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL3 REQUIRED)

add_library(sparrow_lib)

target_sources(sparrow_lib
  PRIVATE
    src/pipeline/vertex_stage.cpp
    src/pipeline/raster_stage.cpp
    src/pipeline/fragment_stage.cpp
    src/windowing/window_init.cpp
  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS 
      include
    FILES
      include/sparrow_rasterizer/pipeline/vertex_stage.hpp
      include/sparrow_rasterizer/pipeline/raster_stage.hpp
      include/sparrow_rasterizer/pipeline/fragment_stage.hpp
      include/sparrow_rasterizer/windowing/window_init.hpp
)

add_executable(rasterizer
  src/main.cpp
)

target_link_libraries(rasterizer
  PRIVATE
    sparrow_lib
    SDL3::SDL3
)
