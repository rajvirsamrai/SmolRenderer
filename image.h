class Colour {
    public:
        unsigned char rgb[3];
        Colour(unsigned char r, unsigned char g, unsigned char b);
};

class Image {
    public:
        int width, height;
        unsigned char *pixels;

        Image(int width, int height);
        ~Image();
        void set(int x, int y, Colour c);
        void save(const char *filename);
};