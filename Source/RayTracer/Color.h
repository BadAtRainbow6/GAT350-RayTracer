#pragma once
#include <glm/glm.hpp>
using color3_t = glm::vec3;
using color4_t = glm::vec4;
using rgba_t = uint32_t;
class Color {

public:
    inline color4_t RGBAToColor(const rgba_t& rgba) {
        return color4_t(
            ((rgba >> 24) & 0xFF) / 255.0f,
            ((rgba >> 16) & 0xFF) / 255.0f,
            ((rgba >> 8) & 0xFF) / 255.0f,
            (rgba & 0xFF) / 255.0f
        );
    }
    inline rgba_t ColorToRGBA(const color4_t& color) {
        return ((uint32_t)(color.a * 255.0f) << 24) |
            ((uint32_t)(color.r * 255.0f) << 16) |
            ((uint32_t)(color.g * 255.0f) << 8) |
            ((uint32_t)(color.b * 255.0f));
    }
};