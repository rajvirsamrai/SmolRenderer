#include <cstdlib>
#include <utility>

#include "line.h"
#include "image.h"

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