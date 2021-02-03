#include "image.h"
#include "model.h"

#include <cstdlib>
#include <iostream>
#include <utility>

extern void line(int x0, int y0, int x1, int y1, Colour &c, Image &i);
extern void wireframe(Model &obj, Colour &c, Image &img);

const int height = 2000;
const int width = 2000;

int main(int argc, char** argv){
    if(argc != 2){
        std::cerr << "usage: " << argv[0] << " FILENAME" << "\n";
    }

    Image render(height, width);
    Colour white(255, 255, 255);
    Model head;
    head.load(argv[1]);
    wireframe(head, white, render);
    render.save("test.tga");
}

void wireframe(Model &obj, Colour &c, Image &img){
    Face f;

    for(int i = 0; i < (int) obj.faces.size(); i++){
        f = obj.faces[i];

        Vec3 v0 = obj.vertices[f.v[0] - 1];
        Vec3 v1 = obj.vertices[f.v[1] - 1];
        Vec3 v2 = obj.vertices[f.v[2] - 1];

        int x0 = (v0.x + 1.0) * width/2.0;
        int y0 = (v0.y + 1.0) * height/2.0;

        int x1 = (v1.x + 1.0) * width/2.0;
        int y1 = (v1.y + 1.0) * height/2.0;

        int x2 = (v2.x + 1.0) * width/2.0;
        int y2 = (v2.y + 1.0) * height/2.0;

        line(x0, y0, x1, y1, c, img);
        line(x0, y0, x2, y2, c, img);
        line(x1, y1, x2, y2, c, img);
    }
}

void line(int x0, int y0, int x1, int y1, Colour &c, Image &i){
    bool transposed = false;

    if(std::abs(x0 - x1) < std::abs(y0 - y1)){    // Transpose because we want the "longer" side to "stretch across" the X axis
        std::swap(x0, y0);
        std::swap(x1, y1);
        transposed = true;
    }

    if(x1 < x0){                        // We want to progress from left to right
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dy = y1-y0;
    int dx = x1-x0;
    int derror = std::abs(dy)*2;
    int error = 0;

    int y = y0;
    int yinc = (y1 > y0) ? 1 : -1;

    if(transposed){                     // Moved the if statement outside the for loop
        for(int x = x0; x <= x1; x++){
            i.set(y, x, c);
            error += derror;
            if(error > dx){
                y += yinc;
                error -= dx*2;
            }
        }
        
    } else {
        for(int x = x0; x < x1; x++){
            i.set(x, y, c);
            error += derror;
            if(error > dx){
                y += yinc;
                error -= dx*2;
            }
        }
    }
}