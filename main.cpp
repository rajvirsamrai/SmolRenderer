#include "image.h"
#include "model.h"

#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <utility>

extern void line(int x0, int y0, int x1, int y1, Colour &c, Image &i);
extern void wireframe(Model &obj, Colour &c, Image &img);
extern void flat_shade_render(Model &obj, Image &img);
extern void triangle_ls(int x0, int y0, int x1, int y1, int x2, int y2, Colour &c, Image &img);
extern void triangle_bb(int x0, int y0, int x1, int y1, int x2, int y2, Colour &c, Image &img);
// TODO: MAKE A GEOMETRY CLASS

const int height = 800;
const int width = 800;

int main(int argc, char** argv){
    if(argc != 2){
        std::cerr << "usage: " << argv[0] << " FILENAME" << "\n";
    }

    Image render(height, width);
    Model head;
    head.load(argv[1]);

    flat_shade_render(head, render);

    render.save("test.tga");
}

void flat_shade_render(Model &obj, Image &img){
    Face f;
    Colour c(0, 0, 0);

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

        for(int i = 0; i < 3; i++){
            c.rgb[i] = rand()%255;
        }

        triangle_bb(x0, y0, x1, y1, x2, y2, c, img);
    }
}

Vec3 cross(float Vx, float Vy, float Vz, float Wx, float Wy, float Wz){
    return Vec3(Vy*Wz - Vz*Wy, Vz*Wx - Vx*Wz, Vx*Wy - Vy*Wx);
}

bool in_bounding_box(int x0, int y0, int x1, int y1, int x2, int y2, int Px, int Py){
    // Let x0/y0 be A, x1/y1 be B, x2/y2 be C
    int ABx = x1 - x0;
    int ACx = x2 - x0;
    int PAx = x0 - Px;

    int ABy = y1 - y0;
    int ACy = y2 - y0;
    int PAy = y0 - Py;

    Vec3 bc_cords = cross(ABx, ACx, PAx, ABy, ACy, PAy);

    // Check if triangle is degenerate
    if(std::abs(bc_cords.z) < 1){
        return false;
    }

    float a = 1.0 - (bc_cords.x + bc_cords.y)/bc_cords.z;
    float b = bc_cords.y/bc_cords.z;
    float c = bc_cords.x/bc_cords.z;

    return (0 <= a && 0 <= b && 0 <= c);
}

void triangle_bb(int x0, int y0, int x1, int y1, int x2, int y2, Colour &c, Image &img){
    int bb_min_x = std::max(std::min(std::min(x0, x1), x2), 0);
    int bb_min_y = std::max(std::min(std::min(y0, y1), y2), 0);
    int bb_max_x = std::min(std::max(std::max(x0, x1), x2), img.width);
    int bb_max_y = std::min(std::max(std::max(y0, y1), y2), img.height);

    for(int x = bb_min_x; x <= bb_max_x; x++){
        for(int y = bb_min_y; y <= bb_max_y; y++){
            if(in_bounding_box(x0, y0, x1, y1, x2, y2, x, y)){
                img.set(x, y, c);
            }
        }
    }

    return;
}

void triangle_ls(int x0, int y0, int x1, int y1, int x2, int y2, Colour &c, Image &img){
    if(y0 < y1){
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    if(y0 < y2){
        std::swap(x0, x2);
        std::swap(y0, y2);
    }
    if(y1 < y2){
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    int total_height = y0 - y2 + 1;
    int short_side_a_height = y1 - y2 + 1;
    int short_side_b_height = y0 - y1 + 1;
    float tallest_side_progress;
    float short_side_progress;
    int x_left_bound;
    int x_right_bound;

    for(int y = y2; y <= y0; y++){
        tallest_side_progress = (float) (y - y2)/total_height;
        x_left_bound = tallest_side_progress*(x0 - x2) + x2;
        if(y <= y1){
            short_side_progress = (float) (y-y2)/short_side_a_height;
            x_right_bound = x2 + short_side_progress*(x1 - x2);
        } else {
            short_side_progress = (float) (y-y1)/short_side_b_height;
            x_right_bound = x1 + short_side_progress*(x0 - x1);
        }

        line(x_left_bound, y, x_right_bound, y, c, img);
    }

    return;
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

    if(std::abs(x0 - x1) < std::abs(y0 - y1)){      // Transpose because we want the "longer" side to "stretch across" the X axis
        std::swap(x0, y0);
        std::swap(x1, y1);
        transposed = true;
    }

    if(x1 < x0){                                    // We want to progress from left to right
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
        for(int x = x0; x <= x1; x++){
            i.set(x, y, c);
            error += derror;
            if(error > dx){
                y += yinc;
                error -= dx*2;
            }
        }
    }
}