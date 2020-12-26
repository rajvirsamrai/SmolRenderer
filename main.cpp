#include "image.h"

int main(){
    Image render(100, 100);
    Colour red(255, 0, 0);
    for(int i = 0; i < 100; i++){
        render.set(i, i, red);
    }
    render.save("test.tga");
    return 0;
}