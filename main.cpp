#include <iostream>
// #include "Image.h"
// #include "Image.cpp"
#include "Bitmap.h"
#include "imageMatrix.h"
#include "imageMatrix.cpp"
#include "Bitmap.cpp"

int main()
{
    int width = 200;
    int height = 200;

    imageMatrix *matrix = new imageMatrix(width, height);

    matrix->generateDefaultImage();


    /*Probando funciones de dibujo*/

    matrix->line(Color(0, 192, 255), 2, 4, 5, 6, 2);
    // matrix->line(Color(0, 0, 0), 40, 20, 10, 20, 2);
    // matrix->line(Color(0, 0, 0), 40, 80, 40, 10, 1);
    // matrix->line(Color(0, 0, 0), 80, 60, 40, 22, 2);
    // matrix->line(Color(0, 0, 0), 10, 10, 30, 20, 1);
    // matrix->pencil(Color(14, 74, 139), 4, 10, 1);
    // matrix->pencil(Color(14, 74, 139), 4, 11, 1);
    // matrix->pencil(Color(14, 74, 139), 4, 12, 1);
    // matrix->pencil(Color(14, 74, 139), 4, 13, 1);
    // matrix->pencil(Color(14, 74, 139), 4, 14, 1);
    // matrix->pencil(Color(14, 74, 139), 4, 15, 1);
    // matrix->pencil(Color(14, 74, 139), 4, 16, 1);
    // matrix->pencil(Color(14, 74, 139), 4, 17, 1);
    // matrix->pencil(Color(14, 74, 139), 5, 17, 1);
    // matrix->pencil(Color(14, 74, 139), 6, 17, 1);


    /*Probando figuras*/

    matrix->rectangle(Color(229, 56, 19), 20, 20, 50, 60, 2);
    // matrix->square(Color(172, 236, 240), 190, 190, 10, 10,2);
    // matrix->triangleIso(Color(8, 147, 157), 20, 20, 70, 80,2);
    // matrix->triangleEsc(Color(233, 67, 201), 30, 100, 70, 150, 80, 60, 2);
    // matrix->triangleRec(Color(33, 222, 43), 150, 150, 190, 170, 2);
    // matrix->rhombus(Color(0, 0, 0), 70, 70, 110, 150, 2);
    matrix->circle(Color(0,0,0), 10,10,120,190);
    

    /*Probando funciones de filtros, borrador, rotaciones entre otras*/

    // matrix->erase(4, 10, 2);
    // matrix->erase(20, 20, 1);   
    // matrix->erase(2, 4, 2);
    matrix->paintFill(Color(255,255,255),Color(65,44,87),190,190);
    // matrix->rotate();
    // matrix->rotate();
    // matrix->rotate();
    // matrix->rotate();
    //matrix->bayerFilter();

    
    /*Ejecutando funciones para exportar bmp*/

    matrix->generatePixelArray();
    int size = matrix->getPixelArraySize();
    Bitmap *exportFistImage = new Bitmap("bayerFilter", matrix->getWidth(), matrix->getHeight(), matrix->getPixelArray(), size);




    Bitmap *importNewImage = new Bitmap("out.bmp");
    imageMatrix *newImage = new imageMatrix(importNewImage->getArray(), importNewImage->getHeight(), importNewImage->getWidth());
    newImage->circle(Color(0,0,0), 20,20,120,190);

    newImage->paintFill(Color(255,255,255),Color(65,44,87),190,190);

    newImage->generatePixelArray();
    Bitmap *exportSecondImg = new Bitmap("penguin", newImage->getWidth(), newImage->getHeight(), newImage->getPixelArray(), newImage->getPixelArraySize());




    

    return 0;
}