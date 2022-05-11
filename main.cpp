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

    // matrix->setColor(Color(123,213,1),50,52);
    // matrix->setColor(Color(123,213,1),50,53);
    // matrix->setColor(Color(123,213,1),50,54);
    // matrix->setColor(Color(123,213,1),50,55);
    // matrix->setColor(Color(123,213,1),50,56);
    // matrix->setColor(Color(123,213,1),50,57);
    // matrix->setColor(Color(123,213,1),50,58);

    // matrix->pen(Color(0,192,255), 25,20,80,90,1);


    // matrix->setColor(Color(0, 0, 0), 1, 2);
    // matrix->setColor(Color(0, 0, 0), 2, 2);
    // matrix->setColor(Color(0, 0, 0), 3, 2);
    // matrix->setColor(Color(0, 0, 0), 4, 2);


    // matrix->line(Color(0,0,0), 2,4,5,6);
    // matrix->line(Color(0,0,0), 40,20,10,20);
    // matrix->line(Color(0,0,0), 40,80,40,10);
    // matrix->line(Color(0,0,0), 80,60,40,22);
    // matrix->line(Color(0,0,0), 10,10,30,20);
    // matrix->pencil(Color(14,74,239), 400,100,1);
    // matrix->pencil(Color(14,74,239), 400,150,2);
    // matrix->pencil(Color(14,74,239), 400,10,3);
    matrix->rectangle(Color(0,0,0), 10,10,50,60);
    //matrix->rectangle(Color(0,0,0), 45,30,20,15);
    matrix->square(Color(0,0,0), 190,190,10,10);
    matrix->triangleIso(Color(0,0,0), 20,20,70,80);
    matrix->triangleEsc(Color(0,0,0), 30,100,70,150,80,60);
    matrix->triangleRec(Color(0,0,0), 150,150,190,170);
    matrix->rhombus(Color(0,0,0), 70,70,110,150);
    
    // matrix->printMatrix();

    // matrix->rotate();
    // matrix->rotate();
    // matrix->rotate();

    matrix->generatePixelArray();

    // std::cout<<"IMPRIME MATRIZ"<<std::endl;

    // matrix->printMatrix();
    
    int size = matrix->getPixelArraySize();

    Bitmap Bitmap("hola", matrix->getWidth(), matrix->getHeight(), matrix->getPixelArray(), size);


    return 0;
}