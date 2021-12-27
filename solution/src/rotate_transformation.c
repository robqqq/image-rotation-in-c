//
// Created by robq on 13.12.2021.
//

#include "rotate-transformation.h"

#include "image.h"

struct image rotate( struct image const source ) {
    struct image new_img = image_init(source.height, source.width);
    for (int32_t i = 0; i < source.height; i++) {
        for (int j = 0; j < source.width; j++) {
            set_pixel_by_coordinates(&new_img, get_pixel_by_coordinates(&source, j, source.height - i - 1),
                                     i, j);
        }
    }
    return new_img;
}
