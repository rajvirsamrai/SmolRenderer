#include <iostream>
#include <fstream>
#include <cstring>

#include "image.h"


/*
Init the RGB data from the parameters into the corresponding array indices.
*/
Colour::Colour(unsigned char r, unsigned char g, unsigned char b){
    rgb[0] = b;
    rgb[1] = g;
    rgb[2] = r;
}


/*
Init the image property variables and the pixel data array.
*/
Image::Image(int width, int height){
    this->width = width;
    this->height = height;
    this->size = width*height*3;

    pixels = new unsigned char[this->size];
    memset(pixels, 0, this->size);
}

/*
Delete the pixel data array before destroying the image object.
*/
Image::~Image(){
    delete pixels;
}

/*
Set the colour of a pixel in the pixel array. I.E update the RGB data.
*/
void Image::set(int x, int y, Colour &c){
    if(x < 0 || x >= width || y < 0 || y >= height){
        return;
    } else {
        memcpy(pixels+(((width*y) + x)*3), c.rgb, 3);
    }
}

/*
Save pixel data to an image file in the TrueVision .tga file format.
*/
void Image::save(const char *filename){
    std::ofstream output(filename, std::ios::binary);
    if(!output.is_open()){
        return;
    }

    // HEADER
    char buf[18];
    memset(buf, 0, 2);                              // No Image ID Field, No colour map
    memset(buf+2, 2, 1);                            // Data Type 2:Unmapped RGB
    memset(buf+3, 0, 9);                            // Offsets 3 to 7 are ignored because we don't have a colour map.
                                                    // 8-9 are X origin, 10-11 are Y origin
    memset(buf+12, (width & 0x00FF), 1);            // Lower order bits for width
    memset(buf+13, (width & 0xFF00) / 256, 1);      // Higher order bits for width
    memset(buf+14, (height & 0x00FF), 1);           // Lower order bits for height
    memset(buf+15, (height & 0xFF00) / 256, 1);     // Higher order bits for height
    memset(buf+16, 24, 1);                          // 24 bits per pixel
    memset(buf+17, 0, 1);                           // Image descriptor
    output.write(buf, 18);

    // PIXELS
    output.write((char *) pixels, this->size);
    output.close();
}