#include "Bitmap.h"

using namespace std;
/**
 * @brief Construct a new Bitmap:: Bitmap object
 * 
 * @param imgName images name to save the file
 * @param width contains the width dimension 
 * @param height contains the height dimension 
 * @param pixelArray matrix information convert into an array 
 * @param pixelArraySize array size 
 */
Bitmap::Bitmap(std::string imgName, int width, int height, unsigned char *pixelArray, int pixelArraySize)
{
    this->height = height;
    this->width = width;
    bmpPixelArray = pixelArray;

    generateBitmapImage(imgName, pixelArraySize);
}
/**
 * @brief Construct a new Bitmap:: Bitmap object
 * 
 * @param imgPath image name that it is uploaded
 */
Bitmap::Bitmap(std::string imgPath)
{
    this->name = imgPath;
    read();
}
/**
 * @brief Read bmp file form disk 
 * 
 */
void Bitmap::read()
{
    std::ifstream f;
    f.open(this->name, std::ios::in | std::ios::binary);

    if (!f.is_open())
    {
        std::cout << "File could not be open\n";
        return;
    }
    unsigned char fileHeader[FILE_HEADER_SIZE];
    f.read(reinterpret_cast<char *>(fileHeader), FILE_HEADER_SIZE);

    if (fileHeader[0] != 'B' || fileHeader[1] != 'M')
    {
        std::cout << "The specified path is not a bitmap image" << std::endl;
        f.close();
        return;
    }

    unsigned char informationHeader[INFO_HEADER_SIZE];
    f.read(reinterpret_cast<char *>(informationHeader), INFO_HEADER_SIZE);

    int fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16) + (fileHeader[5] << 24);

    width = informationHeader[4] + (informationHeader[5] << 8) + (informationHeader[6] << 16) + (informationHeader[7] << 24);
    height = informationHeader[8] + (informationHeader[9] << 8) + (informationHeader[10] << 16) + (informationHeader[11] << 24);

    int pixelArraySize = width * height * (BITS_PER_PIXEL / 8);
    paddingBytes = (4 - (width * BITS_PER_PIXEL / 8) % 4) % 4;
    bmpPixelArray = (unsigned char *)malloc(pixelArraySize);

    int c = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            unsigned char color[3];
            f.read(reinterpret_cast<char *>(color), 3);
            bmpPixelArray[c] = static_cast<float>(color[2]) ;
            bmpPixelArray[c + 1] = static_cast<float>(color[1]) ;/// 255.0f;
            bmpPixelArray[c + 2] = static_cast<float>(color[0]) ;/// 255.0f;
            c = c + 3;
        }
        f.ignore(paddingBytes);
    }

    f.close();
    std::cout << "File imported read " << std::endl;
}
/**
 * @brief Gemerate the bmp file out of a array information 
 * 
 * @param imgName name assign to bmp file 
 * @param pixelArraySize array's size 
 */
void Bitmap::generateBitmapImage(std::string imgName, int pixelArraySize)
{
    std::string fileName = imgName + ".bmp";

    FILE *imageFile = fopen(fileName.c_str(), "wb");

    unsigned char *fileHeader = createBitmapFileHeader();
    unsigned char *infoHeader = createBitmapInfoHeader();

    fwrite(fileHeader, 1, FILE_HEADER_SIZE, imageFile);
    fwrite(infoHeader, 1, INFO_HEADER_SIZE, imageFile);
    fwrite(bmpPixelArray, 1, pixelArraySize, imageFile);

    cout << "Bitmap Image created succesfully!" << endl;
}

/**
 * @brief It creates the file header fro bmp file 
 * 
 * @return unsigned char* this char contains the file header information 
 */
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
/**
 * @brief It created the file information header
 * 
 * @return unsigned char* this char contains the file information header information 
 */
unsigned char *Bitmap::createBitmapInfoHeader()
{
    int imageSize = height * width * (BITS_PER_PIXEL / 8);

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
/**
 * @brief It fills bytes for bmp file 
 * 
 * @param array 
 * @param value 
 * @param initByte 
 */
void Bitmap::fillFourBytes(unsigned char *array, int value, int initByte)
{
    for (int i = initByte; i < initByte + 4; i++)
    {
        array[i] = (unsigned char)(value >> (8 * (i - initByte)));
    }
}

int Bitmap::getHeight()
{
    return this->height;
}
int Bitmap::getWidth()
{
    return this->width;
}
unsigned char *Bitmap::getArray()
{
    return this->bmpPixelArray;
}
