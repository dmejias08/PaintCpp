#include "imageMatrix.h"

using namespace std;

Color::Color()
    : r(255), g(255), b(255)
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

void imageMatrix::generatePixelArray()
/*Genera un array de cada color de cada pixel para que se pueda leer en bmpHandler*/
{
    pixelArraySize = imgHeight * imgWidth * (BITS_PER_PIXEL / 8);
    paddingBytes = (4 - (imgWidth * BITS_PER_PIXEL / 8) % 4)%4;
    std::cout<<"Padding bytes: "<<paddingBytes<<std::endl;
    pixelArray = (unsigned char *)malloc(pixelArraySize + paddingBytes * imgHeight);
    int c = 0;
    for (int i = imgHeight - 1; i >= 0; i--)
    {

        for (int j = 0; j < imgWidth; j++)
        {

            pixelArray[c] = pixelMatrix[i][j].b;
            pixelArray[c + 1] = pixelMatrix[i][j].g;
            pixelArray[c + 2] = pixelMatrix[i][j].r;
            // std::cout << "Generate pixelArray " << c << pixelArray[c] << " " << pixelArray[c + 1] << " " << pixelArray[c + 2] << std::endl;
            c = c + 3;
        }
        c += paddingBytes;
    }
}
int imageMatrix::getPixelArraySize()
{
    // for (int i = 0; i < pixelArraySize; i++)
    // {
    //     std::cout << i << " " << pixelArray[i] << std::endl;
    // }
    int size = pixelArraySize + paddingBytes * imgHeight;
    return size;
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
            setColor(Color(), i, j);
        }
    }
}

void imageMatrix::erase(int i, int j, int eraserWidth)
/*El método para borrar lo que va hacer es dibujar en blanco usando el metodo pencil*/
{
    pencil(Color(), i, j, eraserWidth);
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
    // std::cout << "(" << i << "," << j << ")"
    //           << " R " << pixelMatrix[i][j].r << " G " << pixelMatrix[i][j].g << " B " << pixelMatrix[i][j].b << std::endl;
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

    // int slope = (jFinal - jInitial)/(iFinal - iFinal);
    // int b = jFinal - slope*iFinal;

    // j = mi + b
    for (int i = iInitial; i <= iFinal; i++)
    {
        for (int j = jInitial; j <= jFinal; j++)
        {
            pencil(color, i, j, lineWidth);
        }
    }
}

void imageMatrix::line(const Color &color, int y1, int x1, int y2, int x2)
/* Función matemática para generar line, note que "y" corresponde a i y  "x" corresponde a j*/
{

    if (x2 - x1 == 0)
    {
        if (y2 < y1)
        {
            int temp = y1;
            y1 = y2;
            y2 = temp;
        }
        for (int i = y1; i <= y2; i++)
        {
            setColor(color, i, x1);
        }
    }
    else
    {

        float m = (float)(y2 - y1) / (float)(x2 - x1);
        printf("m: %f\n", m);
        float b = y1 - (m * x1);
        if (x2 < x1)
        {
            int temp = x1;
            x1 = x2;
            x2 = temp;
        }
        int old_y = round(m * x1 + b);
        for (int i = x1; i <= x2; i++)
        {
            int new_y = round(m * i + b);
            if (new_y == old_y)
            {
                setColor(color, new_y, i);
            }
            else
            {
                if (m >= 0)
                {
                    for (int j = old_y + 1; j <= new_y; j++)
                    {
                        setColor(color, j, i);
                    }
                }
                else
                {
                    for (int j = old_y - 1; j >= new_y; j--)
                    {
                        setColor(color, j, i);
                    }
                }
            }
            old_y = new_y;
        }
    }
}

void imageMatrix::rotate()
{
    Color **oldMatrix = new Color *[imgHeight];
    for (int i = 0; i < imgHeight; i++)
    {
        oldMatrix[i] = new Color[imgWidth];
        for (int j = 0; j < imgWidth; j++)
        {
            oldMatrix[i][j] = this->pixelMatrix[i][j];
        }
    }
    this->deleteMatrix();
    this->switchDimensions();
    this->createMatrix();
    for (int i = 0; i < imgHeight; i++)
    {
        for (int j = 0; j < imgWidth; j++)
        {
            this->pixelMatrix[i][j] = oldMatrix[j][imgHeight - i - 1];
        }
    }
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
    int temp = imgWidth;
    imgWidth = imgHeight;
    imgHeight = temp;
}

int imageMatrix::getHeight()
{
    return imgHeight;
}

int imageMatrix::getWidth()
{
    return imgWidth;
}

void imageMatrix::square(const Color &color, int x1, int y1, int x2, int y2)
{
    int diferentialx = x2-x1;
    int diferentialy = y2-y1;
    int lenghtx = min(abs(diferentialx),abs(diferentialy));
    int lenghty = lenghtx;
    if (diferentialx < 0)
    {
        lenghtx = lenghtx*-1;
    }
    if (diferentialy < 0)
    {
        lenghty = lenghty*-1;
    }
    line(color, y1,x1,y1,x1+lenghtx);
    line(color, y1,x1,y1+lenghty,x1);
    line(color, y1+lenghty,x1,y1+lenghty,x1+lenghtx);
    line(color, y1,x1+lenghtx,y1+lenghty,x1+lenghtx);
    
}
void imageMatrix::rhombus(const Color &color, int x1, int y1, int x2, int y2)
{
    int diferentialx = (x2-x1)/2;
    int diferentialy = (y2-y1)/2;
    line(color, y1,x1+diferentialx,y1+diferentialy,x2);
    line(color, y1,x1+diferentialx,y1+diferentialy,x1);
    line(color, y1+diferentialy,x1,y2,x1+diferentialx);
    line(color, y1+diferentialy,x1,y2,x1+diferentialx);
    line(color, y1+diferentialy,x2,y2,x1+diferentialx);
}
void imageMatrix::triangleIso(const Color &color, int x1, int y1, int x2, int y2)
{
    int diferentialx = (x2-x1)/2;
    line(color, y1,x1+diferentialx,y2,x2);
    line(color, y1,x1+diferentialx,y2,x1);
    line(color, y2,x1,y2,x2);
}
void imageMatrix::triangleRec(const Color &color, int x1, int y1, int x2, int y2)
{
    line(color, y1,x1,y2,x2);
    line(color, y1,x1,y2,x1);
    line(color, y2,x1,y2,x2);
}
void imageMatrix::triangleEsc(const Color &color, int x1, int y1, int x2, int y2, int x3, int y3)
{
    line(color, y1,x1,y2,x2);
    line(color, y1,x1,y3,x3);
    line(color, y2,x2,y3,x3);
}
void imageMatrix::rectangle(const Color &color, int x1, int y1, int x2, int y2)
{
    line(color, y1,x1,y2,x1);
    line(color, y1,x1,y1,x2);
    line(color, y1,x2,y2,x2);
    line(color, y2,x1,y2,x2);
}
void imageMatrix::elipse(const Color &color, int x1, int y1, int x2, int y2)
{   
    int x = min(x1,x2);
    int y = min(y1,y2);
    int diferentialx = abs(x2-x1);
    int diferentialy = abs(y2-y1);
    int h = x + diferentialx/2;
    int k = y + diferentialy/2;
    int a2 = diferentialx*diferentialx/4;
    int b2 = diferentialy*diferentialy/4;
    for (float paintx = (float)x; paintx <= x + diferentialx; paintx=paintx+0.001)
    {
        float painty1 = (float)sqrt((1-(float)((paintx-h)*(paintx-h))/a2)*b2)+k;
        float painty2 = -1*(float)sqrt((1-(float)((paintx-h)*(paintx-h))/a2)*b2)+k;
        setColor(color, painty1, paintx);
        setColor(color, painty2, paintx);
    }
    
        
}
void imageMatrix::circle(const Color &color, int x1, int y1, int x2, int y2)
{
    int diferentialx = x2-x1;
    int diferentialy = y2-y1;
    int lenght = min(abs(diferentialx),abs(diferentialy));
    int x3 = min(x1,x2);
    int y3 = min(y1,y2);
    int x4 = x3 + lenght;
    int y4 = y3 + lenght;
    elipse(color,x3,y3,x4,y4);
}
void imageMatrix::paintFill(const Color &colorPicked, const Color &newColor, int x1, int y1)
{
    if (x1 < imgWidth && y1 < imgHeight && x1 >= 0 && y1 >= 0)
    {
        Color currentColor = getColor(y1,x1);
        if (currentColor.b == colorPicked.b && currentColor.g == colorPicked.g && currentColor.r == colorPicked.r)
        {
            setColor(newColor, y1, x1);
            paintFill(colorPicked, newColor,x1-1,y1);
            paintFill(colorPicked, newColor,x1+1,y1);
            paintFill(colorPicked, newColor,x1,y1-1);
            paintFill(colorPicked, newColor,x1,y1+1);
        }
    }
}