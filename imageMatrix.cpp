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
imageMatrix::imageMatrix(unsigned char* arrayPixel, int height, int width)
{
    imgHeight = height;
    imgWidth = width;
    this->createMatrix();
    this->generateMatrix(arrayPixel);
}

imageMatrix::~imageMatrix()
{
    for (int i = 0; i < imgHeight; i++)
    {
        delete[] pixelMatrix[i];
    }
    delete[] pixelMatrix;

    free(pixelArray);
}

void imageMatrix::generateMatrix(unsigned char* arrayPixel)
{
    int c = 0;
    for (int i = imgHeight - 1; i >= 0; i--)
    {
        for (int j = 0; j < imgWidth; j++)
        {
            float r = arrayPixel[c];
            float g = arrayPixel[c + 1];
            float b = arrayPixel[c + 2];
            setColor(Color(r,g,b), i, j);
            c = c + 3;
        }
    }
}
void imageMatrix::generatePixelArray()
/*Genera un array de cada color de cada pixel para que se pueda leer en bmpHandler*/
{
    pixelArraySize = imgHeight * imgWidth * (BITS_PER_PIXEL / 8);
    paddingBytes = (4 - (imgWidth * BITS_PER_PIXEL / 8) % 4) % 4;
    std::cout << "Padding bytes: " << paddingBytes << std::endl;
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
Color imageMatrix::getColor(int i, int j)
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

void imageMatrix::line(const Color &color, int y1, int x1, int y2, int x2, int lineWidth)
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
            pencil(color, i, x1, lineWidth);
        }
    }
    else
    {

        float m = (float)(y2 - y1) / (float)(x2 - x1);
        // printf("m: %f\n", m);
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
                pencil(color, new_y, i, lineWidth);
            }
            else
            {
                if (m >= 0)
                {
                    for (int j = old_y + 1; j <= new_y; j++)
                    {
                        pencil(color, j, i, lineWidth);
                    }
                }
                else
                {
                    for (int j = old_y - 1; j >= new_y; j--)
                    {
                        // pencil(color, i, j, lineWidth);
                        pencil(color, j, i, lineWidth);
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

void imageMatrix::bayerFilter()
{
    for (int i = 0; i < imgHeight; i++)
    {
        for (int j = 0; j < imgWidth; j++)
        {
            Color colorTemp = getColor(i, j);
            float newRGB = 0.65*colorTemp.r/2 + 0.57*colorTemp.g + 0.7*colorTemp.b;
            setColor(Color(newRGB, newRGB, newRGB), i, j);
        }
    }
}

void imageMatrix::sepiaFilter()
{
    for (int i = 0; i < imgHeight; i++)
    {
        for (int j = 0; j < imgWidth; j++)
        {
            Color colorTemp = getColor(i, j);
            float newR = 0.393 * colorTemp.r + 0.769 * colorTemp.g + 0.189 * colorTemp.b;
            float newG = 0.349 * colorTemp.r + 0.686 * colorTemp.g + 0.168 * colorTemp.b;
            float newB = 0.272 * colorTemp.r + 0.534 * colorTemp.g + 0.131 * colorTemp.b;
            setColor(Color(newR, newG, newB), i, j);
        }
    }
}

void imageMatrix::grayScaleFilter()
{
    for (int i = 0; i < imgHeight; i++)
    {
        for (int j = 0; j < imgWidth; j++)
        {
            Color colorTemp = getColor(i, j);
            float formula = 0.3 * colorTemp.r + 0.59 * colorTemp.g + 0.11 * colorTemp.b;
            setColor(Color(formula, formula, formula), i, j);
        }
    }
}
void imageMatrix::negativeFilter()
{
    for (int i = 0; i < imgHeight; i++)
    {
        for (int j = 0; j < imgWidth; j++)
        {
            Color colorTemp = getColor(i, j);
            setColor(Color(255 - colorTemp.r, 255 - colorTemp.g, 255 - colorTemp.b), i, j);
        }
    }
}

void imageMatrix::square(const Color &color, int x1, int y1, int x2, int y2, int lineWidth)
{
    int diferentialx = x2 - x1;
    int diferentialy = y2 - y1;
    int lenghtx = min(abs(diferentialx), abs(diferentialy));
    int lenghty = lenghtx;
    if (diferentialx < 0)
    {
        lenghtx = lenghtx * -1;
    }
    if (diferentialy < 0)
    {
        lenghty = lenghty * -1;
    }
    line(color, y1, x1, y1, x1 + lenghtx, lineWidth);
    line(color, y1, x1, y1 + lenghty, x1, lineWidth);
    line(color, y1 + lenghty, x1, y1 + lenghty, x1 + lenghtx, lineWidth);
    line(color, y1, x1 + lenghtx, y1 + lenghty, x1 + lenghtx, lineWidth);
}
void imageMatrix::rhombus(const Color &color, int x1, int y1, int x2, int y2, int lineWidth)
{
    int diferentialx = (x2 - x1) / 2;
    int diferentialy = (y2 - y1) / 2;
    line(color, y1, x1 + diferentialx, y1 + diferentialy, x2, lineWidth);
    line(color, y1, x1 + diferentialx, y1 + diferentialy, x1, lineWidth);
    line(color, y1 + diferentialy, x1, y2, x1 + diferentialx, lineWidth);
    line(color, y1 + diferentialy, x1, y2, x1 + diferentialx, lineWidth);
    line(color, y1 + diferentialy, x2, y2, x1 + diferentialx, lineWidth);
}
void imageMatrix::triangleIso(const Color &color, int x1, int y1, int x2, int y2, int lineWidth)
{
    int diferentialx = (x2 - x1) / 2;
    line(color, y1, x1 + diferentialx, y2, x2, lineWidth);
    line(color, y1, x1 + diferentialx, y2, x1, lineWidth);
    line(color, y2, x1, y2, x2, lineWidth);
}
void imageMatrix::triangleRec(const Color &color, int x1, int y1, int x2, int y2, int lineWidth)
{
    line(color, y1, x1, y2, x2, lineWidth);
    line(color, y1, x1, y2, x1, lineWidth);
    line(color, y2, x1, y2, x2, lineWidth);
}
void imageMatrix::triangleEsc(const Color &color, int x1, int y1, int x2, int y2, int x3, int y3, int lineWidth)
{
    line(color, y1, x1, y2, x2, lineWidth);
    line(color, y1, x1, y3, x3, lineWidth);
    line(color, y2, x2, y3, x3, lineWidth);
}
void imageMatrix::rectangle(const Color &color, int x1, int y1, int x2, int y2, int lineWidth)
{
    line(color, y1,x1,y2,x1,lineWidth);
    line(color, y1,x1,y1,x2,lineWidth);
    line(color, y1,x2,y2,x2,lineWidth);
    line(color, y2,x1,y2,x2,lineWidth);
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
