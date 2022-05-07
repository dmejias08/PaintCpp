#include "Image.h"
#include "imageMatrix.cpp"
#include <iostream>
#include <fstream>

Image::Image(int width, int height, imageMatrix *matrix)
    :mWidth(width), mHeight(height), mColor(matrix)
{

}
Image::~Image()
{

}

// void Image::Read(const char* path)
// {
//     std::ifstream f;
//     f.open(path, std::ios::in | std::ios::binary);

//     if(!f.is_open()){
//         std::cout<<"File could not be open\n";
//         return;
//     }

//     const int fileHeaderSize = 14;
//     const int informationHeaderSize = 40;

//     unsigned char fileHeader[fileHeaderSize];
//     f.read(reinterpret_cast<char*>(fileHeader),fileHeaderSize);

//     if(fileHeader[0] != 'B' || fileHeader[1] != 'M')
//     {
//         std::cout<< "The specified path is not a bitmap image"<< std::endl;
//         f.close();
//         return;
//     }

//     unsigned char informationHeader[informationHeaderSize];
//     f.read(reinterpret_cast<char*>(informationHeader),informationHeaderSize);

//     int fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16) +(fileHeader[5] << 24);

//     mWidth = informationHeader[4] + (informationHeader[5] << 8) + (informationHeader[6] << 16) + (informationHeader[7] << 24);
//     mHeight = informationHeader[8] + (informationHeader[9] << 8) + (informationHeader[10] << 16) + (informationHeader[11] << 24);

//     mColor.resize(mWidth * mHeight);

//     const int paddingAmount = ((4 - (mWidth * 3) % 4) % 4);


//     for (int y = 0; y < mHeight; y++)
//     {
//         for (int x = 0 ; x < mWidth ; x++)
//         {
//             unsigned char color[3]; 
//             f.read(reinterpret_cast<char*>(color),3);
//             mColor[y*mWidth + x].r = static_cast<float>(color[2])/255.0f;
//             mColor[y*mWidth + x].g = static_cast<float>(color[1])/255.0f;
//             mColor[y*mWidth + x].b = static_cast<float>(color[0])/255.0f;

//         }
//         f.ignore(paddingAmount);
//     }

//     f.close();
//     std::cout << "File read "<< std::endl;
// }
void Image::Export(const char* path)
{
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);

    if(!f.is_open())
    {
        std::cout<<"File could not be open\n";
        return;
    }

    unsigned char bmpPad[3] ={0,0,0};
    const int paddingAmount = ((4 - (mWidth * 3) % 4) % 4);
    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;
    const int fileSize = fileHeaderSize + informationHeaderSize + mWidth*mHeight + paddingAmount*mHeight;


    unsigned char fileHeader[fileHeaderSize];

    // File type
    fileHeader[ 0] = 'B';
    fileHeader[ 1] = 'M';
    //File size
    fileHeader[ 2] = fileSize;
    fileHeader[ 3] = fileSize >>  8;
    fileHeader[ 4] = fileSize >> 16;
    fileHeader[ 5] = fileSize >> 24;
    //Comprension
    fileHeader[ 6] = 0;
    fileHeader[ 7] = 0;
    fileHeader[ 8] = 0;
    fileHeader[ 9] = 0;
    fileHeader[10] = fileHeaderSize + informationHeaderSize;

    unsigned char informationHeader[informationHeaderSize];

    //Header Size
    informationHeader[ 0] = informationHeaderSize;
    //from 0 to 3 are cero
    informationHeader[ 1] = 0;
    informationHeader[ 2] = 0;
    informationHeader[ 3] = 0;
    //image width
    informationHeader[ 4] = mWidth;
    informationHeader[ 5] = mWidth >>  8;
    informationHeader[ 6] = mWidth >> 16;
    informationHeader[ 7] = mWidth >> 24;

    // image height 
    informationHeader[ 8] = mHeight;
    informationHeader[ 9] = mHeight >>  8;
    informationHeader[10] = mHeight >> 16;
    informationHeader[11] = mHeight >> 24;

    //planes
    informationHeader[12] = 1;
    informationHeader[13] = 0;
    informationHeader[14] = 24;
    informationHeader[15] = 0;
    
    informationHeader[16] = 0;
    informationHeader[17] = 0;
    informationHeader[18] = 0;
    informationHeader[19] = 0;


    informationHeader[20] = 0;
    informationHeader[21] = 0;
    informationHeader[22] = 0;
    informationHeader[23] = 0;


    informationHeader[24] = 0;
    informationHeader[25] = 0;
    informationHeader[26] = 0;
    informationHeader[27] = 0;


    informationHeader[28] = 0;
    informationHeader[29] = 0;
    informationHeader[30] = 0;
    informationHeader[31] = 0;


    informationHeader[33] = 0;
    informationHeader[34] = 0;
    informationHeader[35] = 0;
    informationHeader[36] = 0;

    informationHeader[37] = 0;
    informationHeader[38] = 0;
    informationHeader[39] = 0;


    f.write(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
    f.write(reinterpret_cast<char*>(informationHeader), informationHeaderSize);


    for( int y = 0; y < mHeight; y++){

        for ( int x = 0; x < mWidth; x++){
            unsigned char r = static_cast<unsigned char>(mColor->getColor(x,y).r*255.0f); 
            unsigned char g = static_cast<unsigned char>(mColor->getColor(x,y).g*255.0f); 
            unsigned char b = static_cast<unsigned char>(mColor->getColor(x,y).b*255.0f); 

            unsigned char color[] = {b,g,r};
            f.write(reinterpret_cast<char*>(color),3);
        }
        f.write(reinterpret_cast<char*>(bmpPad), paddingAmount);
    }

    f.close();

    std::cout<<"File Created\n";

}