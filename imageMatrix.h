#ifndef ImageMatrix_h
#define ImageMatrix_h

#define BITS_PER_PIXEL 24
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
    int pixelArraySize;
    int imgWidth;
    int imgHeight;
    Color **pixelMatrix;
    unsigned char* pixelArray;

public:
    imageMatrix(int width, int height);
    ~imageMatrix();
    // static imageMatrix* getInstance();
    // static int getHeight();
    // static int getWidth();
    // static void setSize(int width, int height);
    void deleteMatrix();
    void createMatrix();
    void switchDimensions();
    void rotate();
    void generatePixelArray();
    unsigned char* getPixelArray();
    int getPixelArraySize();
    void generateDefaultImage();
    void printMatrix();
    Color getColor(int i, int j) const;
    void setColor(const Color &color, int i, int j);
    void pencil(const Color &color, int i, int j, int lineWidth);
    void pen(const Color &color, int iInitial, int jInitial, int iFinal, int jFinal, int lineWidth);
};


#endif