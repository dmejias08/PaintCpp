#include <iostream>
// #include "Image.h"
// #include "Image.cpp"
#include "BmpHandler.h"
#include "imageMatrix.h"
#include "imageMatrix.cpp"
#include "BmpHandler.cpp"


int main()
{
    int width = 200;
    int height = 200;


    imageMatrix *matrix = new imageMatrix(width,height);

    matrix->generateDefaultImage();



    matrix->line(Color(0,192,255), 2,4,5,6, 2);
    matrix->line(Color(0,0,0), 40,20,10,20, 2);
    matrix->line(Color(0,0,0), 40,80,40,10, 1);
    matrix->line(Color(0,0,0), 80,60,40,22, 2);
    matrix->line(Color(0,0,0), 10,10,30,20, 1);
    matrix->pencil(Color(14,74,139), 4,10,1);
    matrix->pencil(Color(14,74,139), 4,11,1);
    matrix->pencil(Color(14,74,139), 4,12,1);
    matrix->pencil(Color(14,74,139), 4,13,1);
    matrix->pencil(Color(14,74,139), 4,14,1);
    matrix->pencil(Color(14,74,139), 4,15,1);
    matrix->pencil(Color(14,74,139), 4,16,1);
    matrix->pencil(Color(14,74,139), 4,17,1);
    matrix->pencil(Color(14,74,139), 5,17,1);
    matrix->pencil(Color(14,74,139), 6,17,1);
    
    matrix->erase(4,10,2);
    matrix->erase(20,20,1);
    matrix->erase(2,4,2);
    // matrix->printMatrix();

    matrix->rotate();
    matrix->rotate();
    matrix->rotate();
    matrix->rotate();

    matrix->generatePixelArray();

    // std::cout<<"IMPRIME MATRIZ"<<std::endl;

    // matrix->printMatrix();
    
    int size = matrix->getPixelArraySize();

    Bitmap Bitmap("hola", matrix->getWidth(), matrix->getHeight(), matrix->getPixelArray(), size);


    return 0;
}