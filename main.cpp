#include <iostream>
#include "Image.h"
#include "Image.cpp"




int main(){
    const int width = 200;
    const int height = 200;

    imageMatrix *matrix = new imageMatrix(width, height);


    for(int i = 0; i < height ; i++)
    {
        for(int j = 0; j < width; j++){
            matrix->setColor(Color(0,102,255), i , j);
            // std::cout<<"("<<i<<", "<<j<<")"<<" "<<matrix->getColor(i,j).b<<std::endl;
        }
    }

    int n = 55;
    for(int m = 10; m < 35; m++ ){
        matrix->setColor(Color(0,0,0), m, n);
    }


    Image image(width, height, matrix);
    image.Export("image.bmp");


    return 0;
}