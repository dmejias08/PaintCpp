#ifndef Bitmap_h
#define Bitmap_h

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <string>

#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40
#define BITS_PER_PIXEL 24

class Bitmap
{
public:
    Bitmap(std::string imgName, int height, int width, unsigned char *pixelArray, int pixelArraySize);
    void generateBitmapImage(std::string imgName, int pixelArraySize);
    unsigned char* createBitmapFileHeader();
    unsigned char* createBitmapInfoHeader();
    void fillFourBytes(unsigned char *array, int value, int init_byte);
private:
    unsigned char *bmpPixelArray;
    int height;
    int width;
    int paddingBytes;
};
#endif