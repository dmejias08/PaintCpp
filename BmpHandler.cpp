#include "BmpHandler.h"

using namespace std;

Bitmap::Bitmap(std::string imgName,int width, int height, unsigned char *pixelArray, int pixelArraySize)
{
    this->height = height;
    this->width = width;
    bmpPixelArray = pixelArray;

    generateBitmapImage(imgName, pixelArraySize);
}

void Bitmap::generateBitmapImage(std::string imgName, int pixelArraySize)
{
    std::string fileName = imgName + ".bmp";

    FILE *imageFile = fopen( fileName.c_str(), "wb");


    unsigned char *fileHeader = createBitmapFileHeader();
    unsigned char *infoHeader = createBitmapInfoHeader();

    // for(int i = 0; i < FILE_HEADER_SIZE ; i++){
    //     int number = fileHeader[i];
    //     std::cout<<"file header "<<i<<" "<<number<<std::endl;
    // }
    // for(int j = 0; j < INFO_HEADER_SIZE ; j++){
    //     std::cout<<"info header "<<j<<" "<<infoHeader[j]<<std::endl;
    // }






    fwrite(fileHeader, 1, FILE_HEADER_SIZE, imageFile);
    fwrite(infoHeader, 1, INFO_HEADER_SIZE, imageFile);
    fwrite(bmpPixelArray, 1, pixelArraySize, imageFile);

    cout << "Bitmap Image created succesfully!" << endl;
}

unsigned char *Bitmap::createBitmapFileHeader()
{
    int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (width * height * (BITS_PER_PIXEL / 8));

    static unsigned char fileHeader[] = {
        'B', 'M',    /// signature
        0, 0, 0, 0,  /// image file size in bytes
        0, 0, 0, 0,  /// reserved
        54, 0, 0, 0, /// start of pixel array
    };

    fillFourBytes(fileHeader, fileSize, 2);

    return fileHeader;
}

unsigned char *Bitmap::createBitmapInfoHeader()
{
    int imageSize = height * width * (BITS_PER_PIXEL/8);

    static unsigned char infoHeader[] = {
        40, 0, 0, 0,  /// header size
        0, 0, 0, 0,   /// image width
        0, 0, 0, 0,   /// image height
        1, 0,         /// number of color planes
        24, 0,        /// bits per pixel
        0, 0, 0, 0,   /// compression
        0, 0, 0, 0,   /// image size
        19, 11, 0, 0, /// horizontal resolution
        19, 11, 0, 0, /// vertical resolution
        0, 0, 0, 0,   /// colors in color table
        0, 0, 0, 0,   /// important color count
    };

    fillFourBytes(infoHeader, width, 4);
    fillFourBytes(infoHeader, height, 8);
    fillFourBytes(infoHeader, imageSize, 20);

    return infoHeader;
}

void Bitmap::fillFourBytes(unsigned char *array, int value, int initByte)
{
    for (int i = initByte; i < initByte + 4; i++)
    {
        array[i] = (unsigned char)(value >> (8 * (i - initByte)));
    }
}