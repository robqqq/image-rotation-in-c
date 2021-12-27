#include <stdio.h>
#include <sysexits.h>

#include "bmp.h"
#include "file.h"
#include "image.h"
#include "rotate-transformation.h"

int main( int argc, char** argv ) {
    if (argc != 3) {
        fprintf(stderr, "The program requires 2 arguments, you specified %d\n", argc - 1);
        return EX_USAGE;
    }
    FILE* in = NULL;
    if (!file_open(argv[1], &in, "rb")){
        fprintf(stderr, "Can't open file '%s'\n", argv[1]);
        return EX_NOINPUT;
    }
    struct image img = {0};
    switch (from_bmp(in, &img)) {
        case READ_INVALID_BITS:
            fprintf(stderr, "Invalid bits\n");
            file_close(in);
            return EX_DATAERR;
        case READ_INVALID_SIGNATURE:
            fprintf(stderr, "Invalid bmp signature\n");
            file_close(in);
            return EX_DATAERR;
        case READ_INVALID_HEADER:
            fprintf(stderr, "Invalid bmp header\n");
            file_close(in);
            return EX_DATAERR;
        case READ_FROM_NULL_FILE:
            fprintf(stderr, "Can't open file '%s'\n", argv[1]);
            file_close(in);
            return EX_NOINPUT;
        case READ_OK:
            break;
    }
    if(!file_close(in)) {
        fprintf(stderr, "Error while trying to close the file '%s'\n", argv[1]);
        image_destroy(&img);
        return EX_IOERR;
    }
    struct image new_img = rotate(img);
    image_destroy(&img);
    FILE* out = NULL;
    if(!file_open(argv[2], &out, "wb")) {
        fprintf(stderr, "Could not create file '%s' or access is denied\n", argv[2]);
        image_destroy(&new_img);
        return EX_CANTCREAT;
    }
    if (to_bmp(out, &new_img)) {
        fprintf(stderr, "Error while trying to write bmp file\n");
        image_destroy(&new_img);
        file_close(out);
        return EX_IOERR;
    }
    image_destroy(&new_img);
    if (!file_close(out)) {
        fprintf(stderr, "Error while trying to close the file '%s'\n", argv[2]);
        return EX_IOERR;
    }
    return EX_OK;
}
