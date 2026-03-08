cmake_minimum_required(VERSION 4.2)
project (Sparrow_Rasterizer LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL3 REQUIRED)
find_package(glm REQUIRED)
find_package(tinyobjloader REQUIRED)

add_library(sparrow_lib)

target_sources(sparrow_lib
  PRIVATE
    src/pipeline/vertex_stage.cpp
    src/pipeline/raster_stage.cpp
    src/pipeline/fragment_stage.cpp
    src/pipeline/graphics_pipeline.cpp
    src/windowing/window_init.cpp
    src/utils/pixel_buffer.cpp
    src/utils/vertex_type.cpp
    src/utils/triangle_type.cpp
    src/utils/pixel_type.cpp
    src/utils/mesh_type.cpp
    src/utils/model_type.cpp
    src/utils/camera.cpp
    src/utils/scene.cpp
    src/utils/command_type.cpp
    src/loader/obj_loader.cpp
    src/loader/app.cpp
  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS 
      include
    FILES
      include/sparrow_rasterizer/pipeline/vertex_stage.hpp
      include/sparrow_rasterizer/pipeline/raster_stage.hpp
      include/sparrow_rasterizer/pipeline/fragment_stage.hpp
      include/sparrow_rasterizer/pipeline/graphics_pipeline.hpp
      include/sparrow_rasterizer/windowing/window_init.hpp
      include/sparrow_rasterizer/utils/pixel_buffer.hpp
      include/sparrow_rasterizer/utils/vertex_type.hpp
      include/sparrow_rasterizer/utils/triangle_type.hpp
      include/sparrow_rasterizer/utils/pixel_type.hpp
      include/sparrow_rasterizer/utils/mesh_type.hpp
      include/sparrow_rasterizer/utils/model_type.hpp
      include/sparrow_rasterizer/utils/camera.hpp
      include/sparrow_rasterizer/utils/scene.hpp
      include/sparrow_rasterizer/utils/command_type.hpp
      include/sparrow_rasterizer/loader/obj_loader.hpp
      include/sparrow_rasterizer/loader/app.hpp
)

add_executable(rasterizer
  src/main.cpp
)

target_link_libraries(rasterizer
  PRIVATE
    sparrow_lib
    SDL3::SDL3
    glm::glm
    tinyobjloader::tinyobjloader
)
