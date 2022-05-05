#ifndef Image_h
#define Image_h

#include <iostream>
#include <vector>

struct Color
{
    float r, g, b;
    Color();
    Color(float r, float g, float b);
    ~Color();
};

class Image
{
    public:
        Image();
        Image(int width, int height);
        ~Image();

        Color getColor(int x, int y) const;
        void setColor(const Color& color, int x, int y);


        void Read(const char* path);
        void Export(const char* path);

    private:
        int mWidth;
        int mHeight;
        std::vector<Color> mColor;
};

#endif