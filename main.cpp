#include <iostream>
#include "Image.h"
#include "Image.cpp"



int main(){
    const int width = 640;
    const int height = 480;

    Image image(width,height);

    for(int y = 0; y < height ; y++)
    {
        for(int x = 0; x<width ; x++){
            image.setColor(Color(0,102,255), x , y);
            // image.setColor(Color((float)x / (float)width, 1.0f - ((float)x/(float)width),(float)y/(float)height), x , y);
        }
    }
    image.Export("imageprueba.bmp");



    Image copy(0,0);

    copy.Read("imageprueba.bmp");

    copy.Export("copy.bmp");

    return 0;
}