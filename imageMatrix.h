#ifndef ImageMatrix_h
#define ImageMatrix_h

#define BITS_PER_PIXEL 24

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>

struct Color
{
    float r, g, b;
    Color();
    Color(float r, float g, float b);
    ~Color();
};

class imageMatrix
{
private:
    int pixelArraySize;
    int paddingBytes;
    int imgWidth;
    int imgHeight;
    Color **pixelMatrix;
    unsigned char* pixelArray;

public:
    imageMatrix(int width, int height);
    imageMatrix(unsigned char* arrayPixel, int width, int height);
    ~imageMatrix();
    void generateMatrix(unsigned char* arrayPixel);
    void deleteMatrix();
    void createMatrix();
    void switchDimensions();
    void rotate();
    void generatePixelArray();
    unsigned char* getPixelArray();
    int getPixelArraySize();
    void generateDefaultImage();
    void printMatrix();
    void erase(int i, int j, int eraserWidth);
    Color getColor(int i, int j);
    void setColor(const Color &color, int i, int j);
    void pencil(const Color &color, int i, int j, int lineWidth);
    int getHeight();
    int getWidth();
    void line(const Color &color, int x1, int y1, int x2, int y2, int lineWidth);
    void square(const Color &color, int x1, int y1, int x2, int y2, int lineWidth);
    void rhombus(const Color &color, int x1, int y1, int x2, int y2, int lineWidth);
    void triangleIso(const Color &color, int x1, int y1, int x2, int y2, int lineWidth);
    void triangleRec(const Color &color, int x1, int y1, int x2, int y2, int lineWidth);
    void triangleEsc(const Color &color, int x1, int y1, int x2, int y2, int x3, int y3, int lineWidth);
    void rectangle(const Color &color, int x1, int y1, int x2, int y2, int lineWidth);
    void circle(const Color &color, int x1, int y1, int x2, int y2);
    void elipse(const Color &color, int x1, int y1, int x2, int y2);
    void paintFill(const Color &colorPicked, const Color &newColor, int x1, int y1);
    void bayerFilter();
    void sepiaFilter();
    void grayScaleFilter();
    void negativeFilter();

};


#endif
