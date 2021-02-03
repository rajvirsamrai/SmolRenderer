#ifndef IMAGE_H
#define IMAGE_H

/*
Represents a colour as a array of 3 bytes. This corresponds to RGB.
*/
class Colour {
    public:
        unsigned char rgb[3];
        Colour(unsigned char r, unsigned char g, unsigned char b);
};

/*
Represents an image. Raw pixel data is stored in an unsigned char array. The
amount of bytes is equal to width * heigh * 3. Width, height, and total pixels
are also kept in integer variables.
*/
class Image {
    public:
        int width, height, size;
        unsigned char *pixels;

        Image(int width, int height);
        ~Image();
        void set(int x, int y, Colour &c);
        void save(const char *filename);
};

#endif