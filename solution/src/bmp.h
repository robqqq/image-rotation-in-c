//
// Created by robq on 13.12.2021.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION_BMP_H
#define ASSIGNMENT_IMAGE_ROTATION_BMP_H

#include <stdio.h>

#include "image.h"

/*  deserializer   */
enum read_status  {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER,
    READ_FROM_NULL_FILE
    /* коды других ошибок  */
};

enum read_status from_bmp( FILE* in, struct image* img );

/*  serializer   */
enum  write_status  {
    WRITE_OK = 0,
    WRITE_ERROR
    /* коды других ошибок  */
};

enum write_status to_bmp( FILE* out, struct image const* img );

#endif //ASSIGNMENT_IMAGE_ROTATION_BMP_H
