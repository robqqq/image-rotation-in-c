//
// Created by robq on 13.12.2021.
//

#include "image.h"

#include <inttypes.h>
#include <malloc.h>

#include "pixel.h"

struct image image_init (uint32_t width, uint32_t height) {
    struct image img = {0};
    img.width = width;
    img.height = height;
    img.data = malloc (width * height * sizeof (struct pixel));
    return img;
}

void image_destroy (struct image* img) {
    free(img->data);
}

bool set_pixel_by_coordinates (struct image* img, struct pixel pixel, uint32_t x, uint32_t y) {
    if (x < img->width && y < img->height) {
        img->data[y * img->width + x] = pixel;
        return true;
    }
    return false;
}

struct pixel get_pixel_by_coordinates (const struct image* img, uint32_t x, uint32_t y) {
    return img->data[y * img->width + x];
}
