#include <iostream>
#include <fstream>
#include <cstring>

#include "image.h"

Colour::Colour(unsigned char r, unsigned char g, unsigned char b){
    rgb[0] = b;
    rgb[1] = g;
    rgb[2] = r;
}

Image::Image(int width, int height){
    this->width = width;
    this->height = height;
    this->size = width*height*3;

    pixels = new unsigned char[this->size];
    memset(pixels, 0, this->size);
}

Image::~Image(){
    delete pixels;
}

void Image::set(int x, int y, Colour &c){
    if(x < 0 || x >= width || y < 0 || y >= height){
        return;
    } else {
        memcpy(pixels+(((width*y) + x)*3), c.rgb, 3);
    }
}

void Image::save(const char *filename){
    std::ofstream output(filename, std::ios::binary);
    if(!output.is_open()){
        return;
    }

    // HEADER
    char buf[18];
    memset(buf, 0, 2);
    memset(buf+2, 2, 1);
    memset(buf+3, 0, 9);
    memset(buf+12, (width & 0x00FF), 1);            // Lower order bits for width
    memset(buf+13, (width & 0xFF00) / 256, 1);      // Higher order bits for width
    memset(buf+14, (height & 0x00FF), 1);           // Lower order bits for height
    memset(buf+15, (height & 0xFF00) / 256, 1);     // Higher order bits for height
    memset(buf+16, 24, 1);                          // 24 bit
    memset(buf+17, 0, 1);
    output.write(buf, 18);

    // PIXELS
    output.write((char *) pixels, this->size);
    output.close();
}