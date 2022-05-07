#ifndef ImageMatrix_h
#define ImageMatrix_h

struct Color
{
    float r, g, b;
    Color();
    Color(float r, float g, float b);
    ~Color();
};

class imageMatrix
{
private:
    int imgWidth;
    int imgHeight;
    Color **pixelMatrix;

public:
    imageMatrix(int width, int height);
    ~imageMatrix();
    Color getColor(int i, int j) const;
    void setColor(const Color &color, int i, int j);
};


#endif