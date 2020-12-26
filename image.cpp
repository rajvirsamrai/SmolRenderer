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

    pixels = new unsigned char[width*height*3];
    for(int i = 0; i < width*height*3; i++){
        pixels[i] = 0;
    }
}

Image::~Image(){
    delete pixels;
}

void Image::set(int x, int y, Colour c){
    if(x < 0 || x >= width || y < 0 || y >= height){
        return;
    } else {
        int i = ((width*y) + x)*3;
        memcpy(pixels+i, c.rgb, 3);
    }
}

void Image::save(const char *filename){
    std::ofstream output(filename, std::ios::binary);
    if(!output.is_open()){
        return;
    }

    // HEADER
    char buf[18];
    for(int i = 0; i < 18; i++){
        buf[i] = 0;
    }
    memset(buf, 0, 2);
    memset(buf+2, 2, 1);
    memset(buf+3, 0, 9);
    memset(buf+12, (width & 0x00FF), 1);
    memset(buf+13, (width & 0xFF00) / 256, 1);
    memset(buf+14, (height & 0x00FF), 1);
    memset(buf+15, (height & 0xFF00) / 256, 1);
    memset(buf+16, 24, 1);
    memset(buf+17, 0, 1);
    output.write(buf, 18);

    // PIXELS
    output.write((char *) pixels, width*height*3);
    output.close();
}