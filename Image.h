#ifndef Image_h
#define Image_h

#include "imageMatrix.h"
#include <iostream>
#include <vector>

class Image
{
    public:

        Image(int width, int height, imageMatrix *matrix);
        ~Image();



        // void Read(const char* path);
        void Export(const char* path);

    private:
        int mWidth;
        int mHeight;
        imageMatrix *mColor;
};

#endif