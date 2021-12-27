//
// Created by robq on 13.12.2021.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION_FILE_H
#define ASSIGNMENT_IMAGE_ROTATION_FILE_H

#include <stdbool.h>
#include <stdio.h>

bool file_open (const char* path, FILE** file, const char* mode);

bool file_close (FILE* file);

#endif //ASSIGNMENT_IMAGE_ROTATION_FILE_H
