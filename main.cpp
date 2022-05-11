#include <iostream>
// #include "Image.h"
// #include "Image.cpp"
#include "BmpHandler.h"
#include "imageMatrix.h"
#include "imageMatrix.cpp"
#include "BmpHandler.cpp"

int main()
{
    int width = 4;
    int height = 4;

    // imageMatrix::setSize(width, height);

    imageMatrix *matrix = new imageMatrix(width,height);

    matrix->generateDefaultImage();

    // matrix->setColor(Color(123,213,1),50,52);
    // matrix->setColor(Color(123,213,1),50,53);
    // matrix->setColor(Color(123,213,1),50,54);
    // matrix->setColor(Color(123,213,1),50,55);
    // matrix->setColor(Color(123,213,1),50,56);
    // matrix->setColor(Color(123,213,1),50,57);
    // matrix->setColor(Color(123,213,1),50,58);

    // matrix->pen(Color(0,192,255), 10,1,450,1,1);

    matrix->pencil(Color(45, 87, 90), 1, 2, 1);
    // matrix->pencil(Color(10, 40, 55), 27, 20, 2);
    // matrix->pencil(Color(10, 40, 55), 80, 20, 2);
    // matrix->pencil(Color(14,74,239), 20,20,2);
    // matrix->pencil(Color(14,74,239), 400,100,1);
    // matrix->pencil(Color(14,74,239), 400,150,2);
    // matrix->pencil(Color(14,74,239), 400,10,3);

    matrix->generatePixelArray();

    std::cout<<"IMPRIME MATRIZ"<<std::endl;

    matrix->printMatrix();
    
    int size = matrix->getPixelArraySize();

    Bitmap Bitmap(width, height, matrix->getPixelArray(), size);

    // Image image(width, height, matrix);
    // image.Export("default.bmp");

    // matrix->~imageMatrix();
    return 0;
}