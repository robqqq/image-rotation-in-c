//
// Created by robq on 13.12.2021.
//

#include "bmp.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "image.h"

struct __attribute__((packed)) bmp_header{
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

static bool validate_header_signature(const struct bmp_header header) {
    return header.bfType == 0x4D42;
}

static bool test_padding(uint32_t width) {
    return (width * 3) % 4;
}

static uint32_t calculate_padding(uint32_t width) {
    if (test_padding(width)) {
        return 4 - ((width * 3) % 4);
    } else {
        return 0;
    }
}

static bool write_padding(FILE* out, uint32_t width) {
    int8_t zero = 0;
    for (size_t j = 0; j < calculate_padding(width); j++){
        if(!fwrite(&zero, sizeof (int8_t), 1, out)) return false;
    }
    return true;
}

static bool to_image ( FILE* in, const struct bmp_header header, struct image* img) {
    if (header.biHeight <= 0 || header.biWidth <= 0) return false;
    *img = image_init(header.biWidth, header.biHeight);
    fseek(in, header.bOffBits, SEEK_SET);
    for (int32_t i = 0; i < img->height; i++) {
        for (int32_t j = 0; j < img->width; j++) {
            struct pixel pixel = {0};
            if (!fread(&pixel, sizeof (struct pixel), 1, in)) {
                image_destroy(img);
                return false;
            }
            set_pixel_by_coordinates(img, pixel, j, i);
        }
        if (test_padding(img->width)) {
            fseek(in, calculate_padding(img->width), SEEK_CUR);
        }
    }
    return true;
}

static struct bmp_header create_header(const struct image* img) {
    struct bmp_header header = {0};
    header.bfType = 0x4D42;
    header.bfileSize = sizeof (struct bmp_header)
            + img->width * img->height * sizeof(struct pixel)
            + img->height * calculate_padding(img->width);
    header.bOffBits = 54;
    header.biSize = 40;
    header.biWidth = img->width;
    header.biHeight = img->height;
    header.biPlanes = 1;
    header.biBitCount = 24;
    header.biSizeImage = header.bfileSize - 54;
    return header;
}

enum read_status from_bmp( FILE* in, struct image* img ) {
    if (!in) return READ_FROM_NULL_FILE;
    struct bmp_header header = {0};
    if (!fread(&header, sizeof(struct bmp_header), 1, in)) return READ_INVALID_HEADER;
    if (!validate_header_signature(header)) return READ_INVALID_SIGNATURE;
    if (!to_image(in, header, img)) return READ_INVALID_BITS;
    return READ_OK;
}

enum write_status to_bmp( FILE* out, struct image const* img ) {
    struct bmp_header header = create_header(img);
    if (!fwrite(&header, sizeof (struct bmp_header), 1, out)) return WRITE_ERROR;
    for (int32_t i = 0; i < img->height; i++){
        for (int32_t j = 0; j < img->width; j++) {
            struct pixel pixel = get_pixel_by_coordinates(img, j, i);
            if (!fwrite(&pixel, sizeof (struct pixel), 1, out)) return WRITE_ERROR;
        }
        if(!write_padding(out, img->width)) return WRITE_ERROR;
    }
    return WRITE_OK;
}
