
#ifndef RAYTRACER_FILESAVER_H
#define RAYTRACER_FILESAVER_H

#include <iostream>
#include <jpeglib.h>

class fileSaver {
public:
    static int write_JPEG(char * filename, JSAMPLE * image_buffer, int image_width, int image_height,int quality=90);
    static JSAMPLE* read_JPEG(char *filename, int &width, int &height);
};


#endif //RAYTRACER_FILESAVER_H
