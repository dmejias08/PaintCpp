#include <iostream>
// #include "Image.h"
// #include "Image.cpp"
#include "BmpHandler.h"
#include "imageMatrix.h"
#include "imageMatrix.cpp"
#include "BmpHandler.cpp"


int main()
{
    int width = 50;
    int height = 50;


    imageMatrix *matrix = new imageMatrix(width,height);

    matrix->generateDefaultImage();

    // matrix->setColor(Color(123,213,1),50,52);
    // matrix->setColor(Color(123,213,1),50,53);
    // matrix->setColor(Color(123,213,1),50,54);
    // matrix->setColor(Color(123,213,1),50,55);
    // matrix->setColor(Color(123,213,1),50,56);
    // matrix->setColor(Color(123,213,1),50,57);
    // matrix->setColor(Color(123,213,1),50,58);

    // matrix->pen(Color(0,192,255), 25,20,80,90,1);


    matrix->setColor(Color(0, 0, 0), 1, 2);
    matrix->setColor(Color(0, 0, 0), 2, 2);
    matrix->setColor(Color(0, 0, 0), 3, 2);
    matrix->setColor(Color(0, 0, 0), 4, 2);


    // matrix->pencil(Color(14,74,239), 400,100,1);
    // matrix->pencil(Color(14,74,239), 400,150,2);
    // matrix->pencil(Color(14,74,239), 400,10,3);
    matrix->printMatrix();

    // matrix->rotate();
    // matrix->rotate();
    // matrix->rotate();



    matrix->generatePixelArray();

    std::cout<<"IMPRIME MATRIZ"<<std::endl;

    matrix->printMatrix();
    
    int size = matrix->getPixelArraySize();

    Bitmap Bitmap("hola", width, height, matrix->getPixelArray(), size);


    return 0;
}