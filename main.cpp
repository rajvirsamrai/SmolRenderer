#include "image.h"
#include "line.h"

int main(int argc, char** argv){
    Image render(100, 100);
    Colour red(255, 0, 0);
    Colour white(255, 255, 255);
    Colour blue(0, 0, 255);
    line(10, 20, 5, 80, red, render);
    line(20, 10, 90, 5, white, render);
    line(20, 10, 90, 15, white, render);
    line(0, 0, 99, 99, blue, render);
    render.save("test.tga");
}