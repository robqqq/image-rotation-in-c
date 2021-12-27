//
// Created by robq on 13.12.2021.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION_IMAGE_H
#define ASSIGNMENT_IMAGE_ROTATION_IMAGE_H

#include <inttypes.h>
#include <stdbool.h>

#include "pixel.h"

struct image {
    uint32_t width, height;
    struct pixel* data;
};

struct image image_init (uint32_t width, uint32_t height);

void image_destroy (struct image* img);

bool set_pixel_by_coordinates (struct image* img, struct pixel pixel, uint32_t x, uint32_t y);

struct pixel get_pixel_by_coordinates (const struct image* img, uint32_t x, uint32_t y);

#endif //ASSIGNMENT_IMAGE_ROTATION_IMAGE_H
