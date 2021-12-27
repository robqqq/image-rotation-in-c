//
// Created by robq on 13.12.2021.
//

#include "file.h"

#include <stdio.h>

bool file_open (const char* path, FILE** file, const char* mode){
    if (!path) return false;
    *file = fopen(path, mode);
    if (!*file) return false;
    return true;
}

bool file_close (FILE* file){
    if (!file) return false;
    if (fclose(file)) return false;
    return true;
}
