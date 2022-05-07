#include "imageMatrix.h"

Color::Color()
    : r(0), g(0), b(0)
{
}

Color::Color(float r, float g, float b)
    : r(r), g(g), b(b)
{
}
Color::~Color()
{
}
imageMatrix::imageMatrix(int width, int height)
{
    imgHeight = height;
    imgWidth = width;
    this->pixelMatrix = new Color *[height];
    for (int i = 0; i < height; i++)
    {
        this->pixelMatrix[i] = new Color[width];
    }
}

imageMatrix::~imageMatrix()
{
    for (int i = 0; i < imgHeight; i++)
    {
        delete[] pixelMatrix[i];
    }
    delete[] pixelMatrix;
}

Color imageMatrix::getColor(int i, int j) const
{
    return pixelMatrix[i][j];
}
void imageMatrix::setColor(const Color &color, int i, int j)
{
        pixelMatrix[i][j].r = color.r;
        pixelMatrix[i][j].g = color.g;
        pixelMatrix[i][j].b = color.b;
}
