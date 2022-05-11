#ifndef ImageMatrix_h
#define ImageMatrix_h

#define BITS_PER_PIXEL 24

#include <cstdlib>
#include <iostream>
#include <cmath>

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
    ~imageMatrix();
    // static imageMatrix* getInstance();
    // static int getHeight();
    // static int getWidth();
    // static void setSize(int width, int height);
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
    Color getColor(int i, int j) const;
    void setColor(const Color &color, int i, int j);
    void pencil(const Color &color, int i, int j, int lineWidth);
    void pen(const Color &color, int iInitial, int jInitial, int iFinal, int jFinal, int lineWidth);
    int getHeight();
    int getWidth();
    void line(const Color &color, int x1, int y1, int x2, int y2);
    void square(const Color &color, int x1, int y1, int x2, int y2);
    void rhombus(const Color &color, int x1, int y1, int x2, int y2);
    void triangleIso(const Color &color, int x1, int y1, int x2, int y2);
    void triangleRec(const Color &color, int x1, int y1, int x2, int y2);
    void triangleEsc(const Color &color, int x1, int y1, int x2, int y2, int x3, int y3);
    void rectangle(const Color &color, int x1, int y1, int x2, int y2);
};


#endif