#include "sparrow_rasterizer/pipeline/raster_stage.hpp"
#include "sparrow_rasterizer/utils/pixel_buffer.hpp"
#include "sparrow_rasterizer/utils/triangle_type.hpp"
#include "sparrow_rasterizer/utils/vertex_type.hpp"
#include <cstddef>

namespace sparrow_rasterizer {
void RasterStage::render(std::vector<Vertex> &VSInput,
                         std::vector<Model *> models, int width, int height,
                         Buffer &pixel_buffer) {
  uint32_t vertex_offset = 0;
  for (auto model : models) {
    for (auto mesh : model->getMeshes()) {
      for (size_t i = 0; i < mesh.indices.size(); i += 3) {
        Vertex &a = VSInput[mesh.indices[i] + vertex_offset];
        Vertex &b = VSInput[mesh.indices[i + 1] + vertex_offset];
        Vertex &c = VSInput[mesh.indices[i + 2] + vertex_offset];

        // Clip triangle, if necessary
        // TODO
        // Or discard it entirely if outside the clipping volume
        if (!a.inside_clip_space() && !b.inside_clip_space() &&
            !c.inside_clip_space()) {

          continue;
        }

        // Should never happen, but can't be too sure
        if (a.position.w == 0.0f || b.position.w == 0.0f ||
            c.position.w == 0.0f) {
          continue;
        }

        // Transform to NDC by dividing with W
        a.position /= a.position.w;
        b.position /= b.position.w;
        c.position /= c.position.w;

        Triangle tri(a, b, c);

        tri.draw(pixel_buffer, width, height);
      }

      vertex_offset += mesh.vertices.size();
    }
  }
}
} // namespace sparrow_rasterizer
