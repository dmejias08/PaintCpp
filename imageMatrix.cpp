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
/**
 * @brief Construct a new image Matrix::image Matrix object
 * 
 * @param width image dimension 
 * @param height image dimension
 */
imageMatrix::imageMatrix(int width, int height)
/*El contructor genera la matriz relacionada a la imagen de la instancia de clase*/
{

    imgHeight = height;
    imgWidth = width;
    this->createMatrix();
}
/**
 * @brief Construct a new image Matrix::image Matrix object
 * 
 * @param arrayPixel contains the array to convert it into a matrix 
 * @param height image dimension
 * @param width image dimension
 */
imageMatrix::imageMatrix(unsigned char* arrayPixel, int height, int width)
{
    imgHeight = height;
    imgWidth = width;
    this->createMatrix();
    this->generateMatrix(arrayPixel);
}
/**
 * @brief Destroy the image Matrix::image Matrix object
 * 
 */
imageMatrix::~imageMatrix()
{
    for (int i = 0; i < imgHeight; i++)
    {
        delete[] pixelMatrix[i];
    }
    delete[] pixelMatrix;

    free(pixelArray);
}
/**
 * @brief Generate matrix out of an array 
 * 
 * @param arrayPixel contains matrix's information 
 */
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
/**
 * @brief Genera un array de cada color de cada pixel para que se pueda leer en bmpHandler 
 * 
 */
void imageMatrix::generatePixelArray()
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
/**
 * @brief This method generate a default i  mage, it creates a "blank pice of white paper
 * 
 */
void imageMatrix::generateDefaultImage()
{
    for (int i = 0; i < imgHeight; i++)
    {
        for (int j = 0; j < imgWidth; j++)
        {
            setColor(Color(), i, j);
        }
    }
}
/**
 * @brief This methods paints a white pixel
 * 
 * @param i position
 * @param j position
 * @param eraserWidth contains the erase's width 
 */
void imageMatrix::erase(int i, int j, int eraserWidth)
{
    pencil(Color(), i, j, eraserWidth);
}

Color imageMatrix::getColor(int i, int j)
{
    return pixelMatrix[i][j];
}
/**
 * @brief Set a color to a specific pixel according to its position 
 * 
 * @param color RGB color
 * @param i position
 * @param j position
 */
void imageMatrix::setColor(const Color &color, int i, int j)
{
    if(i >= 0 && i < imgHeight && j >= 0 & j < imgWidth){
        pixelMatrix[i][j].r = color.r;
        pixelMatrix[i][j].g = color.g;
        pixelMatrix[i][j].b = color.b;
    }
}
/**
 * @brief It draws a line by painting pixels in a row
 * 
 * @param color RGB color to assign the point  
 * @param i position
 * @param j position
 * @param lineWidth line's width 
 */
void imageMatrix::pencil(const Color &color, int i, int j, int lineWidth)
{
    int lineWidthLimit = lineWidth - 1;
    for (int m = i - lineWidthLimit; m <= i + lineWidthLimit; m++)
    {
        for (int n = j - lineWidthLimit; n <= j + lineWidthLimit; n++)
        {
            setColor(color, m, n);
        }
    }
}
/**
 * @brief It draws a line according to an initial and final point 
 * 
 * @param color RGB color to assing the lin e
 * @param y1 position (i)
 * @param x1 position (j)
 * @param y2 position (i)
 * @param x2 position (j)
 * @param lineWidth 
 */
void imageMatrix::line(const Color &color, int y1, int x1, int y2, int x2, int lineWidth)
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
                        pencil(color, j, i, lineWidth);
                    }
                }
            }
            old_y = new_y;
        }
    }
}
/**
 * @brief It rotates the original matrix
 * 
 */
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
    delete[] oldMatrix;
}
/**
 * @brief Deletes matrix pointers 
 * 
 */
void imageMatrix::deleteMatrix()
{
    for (int i = 0; i < imgHeight; i++)
    {
        delete[] pixelMatrix[i];
    }
    delete[] pixelMatrix;
}
/**
 * @brief Creates a new poninter for matrix 
 * 
 */
void imageMatrix::createMatrix()
{
    this->pixelMatrix = new Color *[imgHeight];
    for (int i = 0; i < imgHeight; i++)
    {
        this->pixelMatrix[i] = new Color[imgWidth];
    }
}
/**
 * @brief It switch temporary matrix's dimensions 
 * 
 */
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
/**
 * @brief It changes the RGB colors in all of matrix's pixels. It would change it in a certain pattern
 * 
 */
void imageMatrix::bayerFilter()
{
    for (int i = 0; i < imgHeight; i++)
    {
        for (int j = 0; j < imgWidth; j++)
        {
            Color colorTemp = getColor(i, j);
            float newRGB = 0.65*colorTemp.r/2 + 0.57*colorTemp.g + 0.7*colorTemp.b;
            while (newRGB > 255){
                newRGB = newRGB - 255;
            }
            setColor(Color(newRGB, newRGB, newRGB), i, j);
        }
    }
}
/**
 * @brief  It changes the RGB colors in all of matrix's pixels. It would change it in a certain pattern
 * 
 */
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
            while (newR > 255){
                newR = newR - 255;
            }
            while (newG > 255){
                newG = newG - 255;
            }
            while (newB > 255){
                newB = newB - 255;
            }
            setColor(Color(newR, newG, newB), i, j);
        }
    }
}
/**
 * @brief  It changes the RGB colors in all of matrix's pixels. It would change it in a certain pattern
 * 
 */
void imageMatrix::grayScaleFilter()
{
    for (int i = 0; i < imgHeight; i++)
    {
        for (int j = 0; j < imgWidth; j++)
        {
            Color colorTemp = getColor(i, j);
            float formula = 0.3 * colorTemp.r + 0.59 * colorTemp.g + 0.11 * colorTemp.b;
            while (formula > 255){
                formula = formula - 255;
            }
            setColor(Color(formula, formula, formula), i, j);
        }
    }
}
/**
 * @brief  It changes the RGB colors in all of matrix's pixels. It would change it in a certain pattern
 * 
 */
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
/**
 * @brief It creates a square by unifying four lines 
 * 
 * @param color RGB color 
 * @param x1 position(j)
 * @param y1 position(i)
 * @param x2 position(j)
 * @param y2 position(i)
 * @param lineWidth line's width 
 */
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
/**
 * @brief it creates a rhombus my unifying five lines depending on the positions 
 * 
 * @param color RGB color 
 * @param x1 position(j)
 * @param y1 position(i)
 * @param x2 position(j)
 * @param y2 position(i)
 * @param lineWidth line's width 
 */
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
/**
 * @brief It creates a figure unifying three lines depending on the positions 
 * 
 * @param color RGB color 
 * @param x1 position(j)
 * @param y1 position(i)
 * @param x2 position(j)
 * @param y2 position(i)
 * @param lineWidth line's width
 */
void imageMatrix::triangleIso(const Color &color, int x1, int y1, int x2, int y2, int lineWidth)
{
    int diferentialx = (x2 - x1) / 2;
    line(color, y1, x1 + diferentialx, y2, x2, lineWidth);
    line(color, y1, x1 + diferentialx, y2, x1, lineWidth);
    line(color, y2, x1, y2, x2, lineWidth);
}
/**
 * @brief It creates a figure unifying three lines depending on the positions 
 * 
 * @param color RGB color 
 * @param x1 position(j)
 * @param y1 position(i)
 * @param x2 position(j)
 * @param y2 position(i)
 * @param lineWidth line's width
 */
void imageMatrix::triangleRec(const Color &color, int x1, int y1, int x2, int y2, int lineWidth)
{
    line(color, y1, x1, y2, x2, lineWidth);
    line(color, y1, x1, y2, x1, lineWidth);
    line(color, y2, x1, y2, x2, lineWidth);
}
/**
 * @brief It creates a figure unifying three lines depending on the positions 
 * 
 * @param color RGB color 
 * @param x1 position(j)
 * @param y1 position(i)
 * @param x2 position(j)
 * @param y2 position(i)
 * @param lineWidth line's width
 */
void imageMatrix::triangleEsc(const Color &color, int x1, int y1, int x2, int y2, int x3, int y3, int lineWidth)
{
    line(color, y1, x1, y2, x2, lineWidth);
    line(color, y1, x1, y3, x3, lineWidth);
    line(color, y2, x2, y3, x3, lineWidth);
}
/**
 * @brief It creates a figure unifying  four lines depending on the positions 
 * 
 * @param color RGB color 
 * @param x1 position(j)
 * @param y1 position(i)
 * @param x2 position(j)
 * @param y2 position(i)
 * @param lineWidth line's width
 */
void imageMatrix::rectangle(const Color &color, int x1, int y1, int x2, int y2, int lineWidth)
{
    line(color, y1,x1,y2,x1,lineWidth);
    line(color, y1,x1,y1,x2,lineWidth);
    line(color, y1,x2,y2,x2,lineWidth);
    line(color, y2,x1,y2,x2,lineWidth);
}
/**
 * @brief It creates an elipse by using a mathematic formula and paints each pixel using the pencil method 
 * 
 * @param color RGB color 
 * @param x1 position(j)
 * @param y1 position(i)
 * @param x2 position(j)
 * @param y2 position(i)
 * @param lineWidth line's width
 */
void imageMatrix::elipse(const Color &color, int x1, int y1, int x2, int y2, int lineWidth)
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
        pencil(color, painty1, paintx, lineWidth);
        pencil(color, painty2, paintx, lineWidth);
    }
}
/**
 * @brief It creates an circle by using a mathematic formula 
 * 
 * @param color RGB color 
 * @param x1 position(j)
 * @param y1 position(i)
 * @param x2 position(j)
 * @param y2 position(i)
 * @param lineWidth line's width
 */
void imageMatrix::circle(const Color &color, int x1, int y1, int x2, int y2, int lineWidth)
{
    int diferentialx = x2-x1;
    int diferentialy = y2-y1;
    int lenght = min(abs(diferentialx),abs(diferentialy));
    int x3 = min(x1,x2);
    int y3 = min(y1,y2);
    int x4 = x3 + lenght;
    int y4 = y3 + lenght;
    elipse(color,x3,y3,x4,y4,lineWidth);
}
/**
 * @brief PaintFill paints an area of pixels that are surrounded by a different color
 * 
 * @param colorPicked Contains the RBG color that is going to be replace 
 * @param newColor RBG color that would be painted 
 * @param x1 position(j)
 * @param y1 position(i)
 */
void imageMatrix::paintFill(const Color &colorPicked, const Color &newColor, int x1, int y1)
{
    if (colorPicked.r != newColor.r && colorPicked.g != newColor.g && colorPicked.b != newColor.b){
        paintFillAux(colorPicked, newColor,x1,y1);
    }
}
/**
 * @brief Auxiliar method for paintFill method 
 * 
 * @param colorPicked Contains the RBG color that is going to be replace 
 * @param newColor RBG color that would be painted 
 * @param x1 position(j)
 * @param y1 position(i)
 */
void imageMatrix::paintFillAux(const Color &colorPicked, const Color &newColor, int x1, int y1)
{
    memoryFlag++;
    if (x1 < imgWidth && y1 < imgHeight && x1 >= 0 && y1 >= 0 && memoryFlag < 350*350)
    {
        Color currentColor = getColor(y1,x1);
        if (currentColor.b == colorPicked.b && currentColor.g == colorPicked.g && currentColor.r == colorPicked.r)
        {
            setColor(newColor, y1, x1);
            paintFillAux(colorPicked, newColor,x1-1,y1);
            paintFillAux(colorPicked, newColor,x1+1,y1);
            paintFillAux(colorPicked, newColor,x1,y1-1);
            paintFillAux(colorPicked, newColor,x1,y1+1);
        }
    }
}

void imageMatrix::setMemoryFlag(int value)
{
    memoryFlag = value;
}
/**
 * @brief It reflects the image horizontally
 * 
 */
void imageMatrix::flipHorizontal(){
    Color **oldMatrix = new Color *[imgHeight];
    for (int i = 0; i < imgHeight; i++)
    {
        oldMatrix[i] = new Color[imgWidth];
        for (int j = 0; j < imgWidth; j++)
        {
            oldMatrix[i][j] = this->pixelMatrix[i][j];
        }
    }
    for (int i = 0; i < imgHeight; i++)
    {
        for (int j = 0; j < imgWidth; j++)
        {
            this->pixelMatrix[i][j] = oldMatrix[i][imgWidth - j - 1];
        }
    }
    delete[] oldMatrix;
}
/**
 * @brief it reflects the image vertically 
 * 
 */
void imageMatrix::flipVertical(){
    Color **oldMatrix = new Color *[imgHeight];
    for (int i = 0; i < imgHeight; i++)
    {
        oldMatrix[i] = new Color[imgWidth];
        for (int j = 0; j < imgWidth; j++)
        {
            oldMatrix[i][j] = this->pixelMatrix[i][j];
        }
    }
    for (int i = 0; i < imgHeight; i++)
    {
        for (int j = 0; j < imgWidth; j++)
        {
            this->pixelMatrix[i][j] = oldMatrix[imgHeight - i - 1][j];
        }
    }
    delete[] oldMatrix;
}
