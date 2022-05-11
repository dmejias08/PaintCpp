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
/*El contructor genera la matriz relacionada a la imagen de la instancia de clase*/
{

    imgHeight = height;
    imgWidth = width;
    // imgHeight = getHeight();
    // imgWidth = getWidth();
    this->createMatrix();
}

imageMatrix::~imageMatrix()
{
    for (int i = 0; i < imgHeight; i++)
    {
        delete[] pixelMatrix[i];
    }
    delete[] pixelMatrix;
}

// static imageMatrix* imageMatrix::getInstance()
// {
//     if(matrixInstance ==  NULL){
//         matrixInstance = new imageMatrix();
//     }
//     return matrixInstance;

// }
// static int imageMatrix::getHeight()
// {
//     return imgHeight;
// }
// static int imageMatrix::getWidth()
// {
//     return imgWidth;
// }
// static void imageMatrix::setSize(int width, int height)
// {
//     imgHeight = height;
//     imgWidth = width;
// }
void imageMatrix::generatePixelArray()
{
    pixelArraySize = imgHeight * imgWidth * (BITS_PER_PIXEL / 8);
    pixelArray = (unsigned char *)malloc(pixelArraySize);
    int c = 0;
    for (int i = imgHeight - 1; i >= 0; i--)
    {

        for (int j = 0; j < imgWidth; j++)
        {

            pixelArray[c] = pixelMatrix[i][j].b;
            pixelArray[c + 1] = pixelMatrix[i][j].g;
            pixelArray[c + 2] = pixelMatrix[i][j].r;
            std::cout << "Generate pixelArray "<<c<< pixelArray[c] << " " << pixelArray[c + 1] << " " << pixelArray[c + 2] << std::endl;
            c = c + 3;
        }
    }
}
int imageMatrix::getPixelArraySize()
{
    for (int i = 0; i < pixelArraySize; i++)
    {
        std::cout << i <<" "<< pixelArray[i] << std::endl;
    }
    return pixelArraySize;
}
unsigned char *imageMatrix::getPixelArray()
{
    return pixelArray;
}
void imageMatrix::printMatrix()
{
    for (int i = 0; i < imgHeight; i++)
    {
        for (int j = 0; j < imgWidth; j++)
        {
            std::cout << "(" << i << "," << j << ")"
                      << " R " << pixelMatrix[i][j].r << " G " << pixelMatrix[i][j].g << " B " << pixelMatrix[i][j].b << std::endl;
        }
    }
}
void imageMatrix::generateDefaultImage()
/*This method generate a default i  mage, it creates a "blank pice of white paper*/
{
    for (int i = 0; i < imgHeight; i++)
    {
        for (int j = 0; j < imgWidth; j++)
        {
            setColor(Color(34, 42, 87), i, j);
        }
    }
}
Color imageMatrix::getColor(int i, int j) const
{
    return pixelMatrix[i][j];
}
void imageMatrix::setColor(const Color &color, int i, int j)
/*  Toma un posición de matriz de pixeles y asig    na los colores correspodientes */
{
    pixelMatrix[i][j].r = color.r;
    pixelMatrix[i][j].g = color.g;
    pixelMatrix[i][j].b = color.b;
    std::cout << "(" << i << "," << j << ")"<< " R " << pixelMatrix[i][j].r << " G " << pixelMatrix[i][j].g << " B " << pixelMatrix[i][j].b << std::endl;
}

void imageMatrix::pencil(const Color &color, int i, int j, int lineWidth)
/*Esta función cumple de función de lápiz. Va a escucha un evento de mouse que toma las coordenadas del pixiel
y en esa posición va a dibujar un punto del color seleccionado por el usuario, tome en cuenta que un conjunto de puntos
forman el dibujo
Se deben elegir el grosor, van a ver tres tipos de grosor*/
{
    std::cout << "Estoy en pencil" << std::endl;
    int lineWidthLimit = lineWidth - 1;
    for (int m = i - lineWidthLimit; m <= i + lineWidthLimit; m++)
    {
        for (int n = j - lineWidthLimit; n <= j + lineWidthLimit; n++)
        {
            setColor(color, m, n);
        }
    }
}
void imageMatrix::pen(const Color &color, int iInitial, int jInitial, int iFinal, int jFinal, int lineWidth)
/*Toma una posición inicial y una posción final y le cambia el color formando una linea. Note que llama a la función punto
y así define el grosor  */
{
    std::cout << "Estoy en pen" << std::endl;
    for (int i = iInitial; i <= iFinal; i++)
    {
        for (int j = jInitial; j <= jFinal; j++)
        {
            pencil(color, i, j, lineWidth);
        }
    }
}

void imageMatrix::rotate()
{
    this->deleteMatrix();

}

void imageMatrix::deleteMatrix()
{
    for (int i = 0; i < imgHeight; i++)
    {
        delete[] pixelMatrix[i];
    }
    delete[] pixelMatrix;
}

void imageMatrix::createMatrix()
{
    this->pixelMatrix = new Color *[imgHeight];
    for (int i = 0; i < imgHeight; i++)
    {
        this->pixelMatrix[i] = new Color[imgWidth];
    }
}

void imageMatrix::switchDimensions()
{
    
}