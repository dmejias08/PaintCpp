#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"
#include "imageMatrix.h"
#include "Bitmap.h"
#include <QColorDialog>
#include <QInputDialog>
#include <QFileDialog>
#include <ostream>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

#define PENCIL          1
#define SQUARE          2
#define RECTANGLE       3
#define ESC             4
#define ISO             5
#define REC             6
#define CIRCLE          7
#define ELIPSE          8
#define LINE            9
#define RHOMBUS         10
#define PAINTFILL       11
#define MAGICSEL        12
#define RECSEL          13
#define FREESEL         14
#define PICKER          15
#define BAYERFILTER     16
#define SEPIAFILTER     17
#define NEGATIVE        18
#define GRAY            19
#define TRACEERASER     20
#define FIGUREERASER    21
#define ZOOMIN          22
#define SELECTREC       23
#define SELECTFREE      24
#define SELECTMAGIC     25

#define MAXIMUMSMOOTHLINE 8
#define INFORMATIONHEIGHT 70

VentanaPrincipal::VentanaPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VentanaPrincipal)
{
    ui->setupUi(this);
}

VentanaPrincipal::~VentanaPrincipal()
{
    delete ui;
}

void VentanaPrincipal::startComponents(){
    canvasPixmap = new QPixmap(getCanvasWidth(),getCanvasHeight());
    this->matrix = new imageMatrix(getCanvasWidth(),getCanvasHeight());
    matrix->generateDefaultImage();
    defaultColor = QColor(Qt::black);
    defaultCanvasColor();
    lineWidth = 2;
    instruction = 0;
    stringAction = "";
    updateSize();

}

void VentanaPrincipal::defaultCanvasColor(){
    painter = new QPainter(canvasPixmap);
    for(int fila = 0;fila<=getCanvasHeight();fila++){
        for(int columna = 0; columna<=getCanvasWidth(); columna++){
            painter->setPen(QPen(QColor(Qt::white)));
            painter->drawPoint(QPoint(columna,fila));
        }
    }
    painter->end();
    loadToFile();
}

void VentanaPrincipal::updateCanvas(){
    painter = new QPainter(canvasPixmap);
    for (int i = 0; i < matrix->getHeight(); i++)
    {
        for (int j = 0; j < matrix->getWidth(); j++)
        {
            painter->setPen(QPen(QColor(matrix->getColor(i,j).r,matrix->getColor(i,j).g,matrix->getColor(i,j).b)));
            painter->drawPoint(QPoint(j,i));
        }
    }
    painter->end();
}

void VentanaPrincipal::updateSize(){
    //Ajusta el tamaño de la ventana, en su posición "x" y "y", con el ancho del lienzo y
    //el alto del lienzo mas 70 pixeles donde se pondrán los botones de los controladores
    this->setGeometry(this->geometry().x(),this->geometry().y(),this->getCanvasWidth(),this->getCanvasHeight()+INFORMATIONHEIGHT);
    this->ui->lblAlto->setText(QString::number(this->getCanvasHeight()));
    this->ui->lblAncho->setText(QString::number(this->getCanvasWidth()));
    this->ui->horizontalSlider->setGeometry(getCanvasWidth()-this->ui->horizontalSlider->width(),
                                            INFORMATIONHEIGHT/2-this->ui->horizontalSlider->height(),
                                            this->ui->horizontalSlider->width(),this->ui->horizontalSlider->height());

}

void VentanaPrincipal::rotateRight(){
    int altotemp = canvasHeight;
    setCanvasHeight(canvasWidth);
    setCanvasWidth(altotemp);
    matrix->rotate();
    matrix->rotate();
    matrix->rotate();
    canvasPixmap = new QPixmap(getCanvasWidth(),getCanvasHeight());
    updateCanvas();
    updateSize();
    loadToFile();
}

void VentanaPrincipal::rotateLeft(){
    int altotemp = canvasHeight;
    setCanvasHeight(canvasWidth);
    setCanvasWidth(altotemp);
    matrix->rotate();
    canvasPixmap = new QPixmap(getCanvasWidth(),getCanvasHeight());
    updateCanvas();
    updateSize();
    loadToFile();
}

void VentanaPrincipal::zoomIn(int sizeFactor){
    Color **copyMatrix = new Color *[matrix->getHeight()*sizeFactor];
    for (int i = 0; i < matrix->getHeight()*sizeFactor; i++)
    {
        copyMatrix[i] = new Color[matrix->getWidth()*sizeFactor];
    }
    for (int i = 0; i < matrix->getHeight(); i++)
    {
        for (int j = 0; j < matrix->getWidth(); j++)
        {
            for (int n = i*sizeFactor+sizeFactor-1; n >= i*sizeFactor; n--){
                for (int m = j*sizeFactor+sizeFactor-1; m >= j*sizeFactor; m--){
                    copyMatrix[n][m] = matrix->getColor(i,j);
                }
            }
        }
    }

    int x = startPoint.x()*sizeFactor - matrix->getWidth()/2;
    int y = startPoint.y()*sizeFactor - matrix->getHeight()/2;
    if (x < 0){
        x = 0;
    }else if (x > matrix->getWidth()){
        x = x/2;
    }if (y < 0){
        y = 0;
    }else if (y > matrix->getHeight()){
        y = y/2;
    }
    painter = new QPainter(canvasPixmap);
    for (int i = 0; i < matrix->getHeight(); i++)
    {
        for (int j = 0; j < matrix->getWidth(); j++)
        {
            painter->setPen(QPen(QColor(copyMatrix[y+i][x+j].r,copyMatrix[y+i][x+j].g,copyMatrix[y+i][x+j].b)));
            painter->drawPoint(QPoint(j,i));
        }
    }
    painter->end();
    update();

    delete[] copyMatrix;
}

void VentanaPrincipal::actionPointPressed(){
    unselectMagic();
    switch (instruction) {
    case PAINTFILL:
        paintFill(defaultColor, startPoint.x(), startPoint.y());
        loadToFile();
        break;
    case ZOOMIN:
        zoomIn(sizeFactor);
        break;
    case FIGUREERASER:
        paintFill(QColor(Qt::white), startPoint.x(), startPoint.y());
        loadToFile();
        break;
    case SELECTMAGIC:
        selectOFF = false;
        if (selectON){
            paintFill(QColor(255-matrix->getColor(selectPoint.y(),selectPoint.x()).r,255-matrix->getColor(selectPoint.y(),selectPoint.x()).g,255-matrix->getColor(selectPoint.y(),selectPoint.x()).b), selectPoint.x(),selectPoint.y());
        }
        paintFill(QColor(255-matrix->getColor(startPoint.y(),startPoint.x()).r,255-matrix->getColor(startPoint.y(),startPoint.x()).g,255-matrix->getColor(startPoint.y(),startPoint.x()).b), startPoint.x(),startPoint.y());
        selectPoint = startPoint;
        selectON = true;
        break;
    case PICKER:
        pickColor();
        break;
    case ESC:
        paintTriangleESC(defaultColor);
        break;
    default:
        break;
    }
}

void VentanaPrincipal::actionButtonPressed(){
    switch (instruction) {
    case SQUARE:
        paintSquare(defaultColor);
        loadToFile();
        break;
    case RECTANGLE:
        paintRectangle(defaultColor);
        loadToFile();
        break;
    case ISO:
        paintTriangleISO(defaultColor);
        loadToFile();
        break;
    case REC:
        paintTriangleREC(defaultColor);
        loadToFile();
        break;
    case LINE:
        paintLine(defaultColor);
        loadToFile();
        break;
    case CIRCLE:
        paintCircle(defaultColor);
        loadToFile();
        break;
    case ELIPSE:
        paintElipse(defaultColor);
        loadToFile();
        break;
    case RHOMBUS:
        paintRhombus(defaultColor);
        loadToFile();
        break;
    case SELECTREC:
        selectRectangle(startPoint.x(),startPoint.y(),endPoint.x(),endPoint.y());
        loadToFile();
        break;
    case PENCIL:
        loadToFile();
        break;
    default:
        break;
    }
}

void VentanaPrincipal::paintSquare(QColor colorToUse){

    matrix->square(Color(colorToUse.red(),colorToUse.green(),colorToUse.blue()),startPoint.x(),startPoint.y(),endPoint.x(),endPoint.y(),lineWidth);
    updateCanvas();
    update();

}

void VentanaPrincipal::paintRectangle(QColor colorToUse){
    matrix->rectangle(Color(colorToUse.red(),colorToUse.green(),colorToUse.blue()),startPoint.x(),startPoint.y(),endPoint.x(),endPoint.y(),lineWidth);
    updateCanvas();
    update();
}

void VentanaPrincipal::paintTriangleESC(QColor colorToUse){
    triangleCounter++;
    if (triangleCounter == 1){
        firstPoint = startPoint;
    } else if (triangleCounter == 2) {
        secondPoint = startPoint;
    } else if (triangleCounter == 3){
        thirdPoint = startPoint;
        matrix->triangleEsc(Color(colorToUse.red(),colorToUse.green(),colorToUse.blue()),firstPoint.x(),firstPoint.y(),secondPoint.x(),secondPoint.y(),thirdPoint.x(),thirdPoint.y(),lineWidth);
        triangleCounter = 0;
        updateCanvas();
        update();
        loadToFile();
    }

}

void VentanaPrincipal::paintTriangleISO(QColor colorToUse){
    matrix->triangleIso(Color(colorToUse.red(),colorToUse.green(),colorToUse.blue()),startPoint.x(),startPoint.y(),endPoint.x(),endPoint.y(),lineWidth);
    updateCanvas();
    update();
}

void VentanaPrincipal::paintTriangleREC(QColor colorToUse){
    matrix->triangleRec(Color(colorToUse.red(),colorToUse.green(),colorToUse.blue()),startPoint.x(),startPoint.y(),endPoint.x(),endPoint.y(),lineWidth);
    updateCanvas();
    update();
}

void VentanaPrincipal::paintRhombus(QColor colorToUse){
    matrix->rhombus(Color(colorToUse.red(),colorToUse.green(),colorToUse.blue()),startPoint.x(),startPoint.y(),endPoint.x(),endPoint.y(),lineWidth);
    updateCanvas();
    update();
}

void VentanaPrincipal::paintCircle(QColor colorToUse){
    matrix->circle(Color(colorToUse.red(),colorToUse.green(),colorToUse.blue()),startPoint.x(),startPoint.y(),endPoint.x(),endPoint.y(), lineWidth);
    updateCanvas();
    update();
}

void VentanaPrincipal::paintElipse(QColor colorToUse){
    matrix->elipse(Color(colorToUse.red(),colorToUse.green(),colorToUse.blue()),startPoint.x(),startPoint.y(),endPoint.x(),endPoint.y(), lineWidth);
    updateCanvas();
    update();
}

void VentanaPrincipal::paintLine(QColor colorToUse){
    matrix->line(Color(colorToUse.red(),colorToUse.green(),colorToUse.blue()),startPoint.y(),startPoint.x(),endPoint.y(),endPoint.x(), lineWidth);
    updateCanvas();
    update();
}

void VentanaPrincipal::paintFill(QColor colorToUse, int x1, int y1){
   matrix->paintFill(matrix->getColor(y1,x1),Color(colorToUse.red(),colorToUse.green(),colorToUse.blue()),x1,y1);
   matrix->setMemoryFlag(0);
   updateCanvas();
   update();
}

void VentanaPrincipal::pickColor(){
    Color temp = matrix->getColor(startPoint.y(),startPoint.x());
    defaultColor.setRed(temp.r);
    defaultColor.setGreen(temp.g);
    defaultColor.setBlue(temp.b);
}

void VentanaPrincipal::selectFree(){

}

void VentanaPrincipal::selectRectangle(int x1, int y1, int x2, int y2){
    painter = new QPainter(canvasPixmap);
    int xMinBound = min(abs(x1),abs(x2));
    int yMinBound = min(abs(y1),abs(y2));
    int xMaxBound = max(abs(x1),abs(x2));
    int yMaxBound = max(abs(y1),abs(y2));
    for (int i = yMinBound; i <= yMaxBound; i++){
        for (int j = xMinBound; j <= xMaxBound; j++){
            if (i >= 0 && i < matrix->getHeight() && j >= 0 && j < matrix->getWidth()){
                painter->setPen(QPen(QColor(255-matrix->getColor(i,j).r,255-matrix->getColor(i,j).g,255-matrix->getColor(i,j).b)));
                painter->drawPoint(QPoint(j,i));
            }
        }
    }
    painter->end();
    update();
}

void VentanaPrincipal::mousePressEvent(QMouseEvent *event){
    updateCanvas();
    update();
    if(0 <= event->pos().x() && event->pos().x() < getCanvasWidth() && INFORMATIONHEIGHT < event->pos().y() && event->pos().y() < getCanvasHeight()+INFORMATIONHEIGHT){
        startPoint = QPoint(event->pos().x(),event->pos().y()-INFORMATIONHEIGHT);
        lastPoint = startPoint;
        actionPointPressed();
    }
}

void VentanaPrincipal::mouseMoveEvent(QMouseEvent *event){
    painter = new QPainter(canvasPixmap);
    if(0 <= event->pos().x() && event->pos().x() < getCanvasWidth() && INFORMATIONHEIGHT < event->pos().y() && event->pos().y() < getCanvasHeight()+INFORMATIONHEIGHT && (instruction == PENCIL || instruction == TRACEERASER || instruction == SELECTFREE)){
        endPoint = QPoint(event->pos().x(),event->pos().y()-INFORMATIONHEIGHT);
        if(instruction == PENCIL){
            paintPencil(defaultColor);
        } else if (instruction == TRACEERASER) {
            paintPencil(QColor(Qt::white));
        } else {
            selectFree();
        }
        lastPoint = endPoint;
        update();
        event->accept();
    }
    painter->end();
}

void VentanaPrincipal::paintPencil(QColor colorToUse){
    QPen pencil(colorToUse);
    QLineF line(lastPoint, endPoint);
    pencil.setWidth(lineWidth*2);
    pencil.setCapStyle(Qt::RoundCap);
    painter->setPen(pencil);
    painter->drawLine(line);
    matrix->line(Color(colorToUse.red(),colorToUse.green(),colorToUse.blue()),lastPoint.y(),lastPoint.x(),endPoint.y(),endPoint.x(),lineWidth);

}

void VentanaPrincipal::mouseReleaseEvent(QMouseEvent *event){
    if(0 <= event->pos().x() && event->pos().x() < getCanvasWidth() && INFORMATIONHEIGHT < event->pos().y() && event->pos().y() < getCanvasHeight()+INFORMATIONHEIGHT){
        endPoint = QPoint(event->pos().x(),event->pos().y()-INFORMATIONHEIGHT);
        actionButtonPressed();
    }
}

void VentanaPrincipal::paintEvent(QPaintEvent *event){
    QPainter *pintor = new QPainter(this);
    pintor->drawPixmap(0,INFORMATIONHEIGHT, *canvasPixmap);
    event->accept();
    pintor->end();
}

int VentanaPrincipal::getCanvasHeight(){
    return this->canvasHeight;
}

void VentanaPrincipal::setCanvasHeight(int _canvasHeight){
    this->canvasHeight = _canvasHeight;
}

int VentanaPrincipal::getCanvasWidth(){
    return this->canvasWidth;
}

void VentanaPrincipal::setCanvasWidth(int _canvasWidth){
    this->canvasWidth = _canvasWidth;
}

void VentanaPrincipal::on_actionGuardar_Imagen_triggered()
{
    QString elnombre = QFileDialog::getSaveFileName(this,"Guardar bmp","C://");
    matrix->generatePixelArray();
    int size = matrix->getPixelArraySize();
    canvasBitmap = new Bitmap(elnombre.toStdString(),matrix->getWidth(),matrix->getHeight(), matrix->getPixelArray(), size);

}

void VentanaPrincipal::on_actionCargar_Imagen_triggered()
{    loadToFile();
    QString filename = QFileDialog::getOpenFileName(this,"Abrir bmp","C://","Bmp file (*.bmp)");
    canvasBitmap = new Bitmap(filename.toStdString());
    canvasHeight = canvasBitmap->getHeight();
    canvasWidth = canvasBitmap->getWidth();
    setCanvasHeight(canvasHeight);
    setCanvasWidth(canvasWidth);
    this->matrix = new imageMatrix(canvasBitmap->getArray(),canvasHeight, canvasWidth);
    canvasPixmap = new QPixmap(getCanvasWidth(),getCanvasHeight());
    updateCanvas();
    updateSize();
    update();
}

void VentanaPrincipal::unselectMagic(){
    if (instruction != SELECTMAGIC && selectOFF){
        paintFill(QColor(255-matrix->getColor(selectPoint.y(),selectPoint.x()).r,255-matrix->getColor(selectPoint.y(),selectPoint.x()).g,255-matrix->getColor(selectPoint.y(),selectPoint.x()).b), selectPoint.x(),selectPoint.y());
        selectON = false;
        selectOFF = false;
    }
}

void VentanaPrincipal::loadFromFile()
{
    string line;
    int i = 0;
    ifstream matrixToLoad ("autosave/slot"+to_string(autoSavedCursor)+".txt");
    cout<<"Boutta open: "<<autoSavedCursor<<endl;
    while (getline (matrixToLoad, line)) {
        int j = 0;
        while (j < matrix->getWidth()){
            string substringRed;
            string substringGreen;
            string substringBlue;
            int colorCounter = 1;
            while (line.length()>1) {
                if (colorCounter == 1){
                    substringRed = line.substr(0, line.find("/"));
                    colorCounter++;
                } else if (colorCounter == 2){
                    substringGreen = line.substr(0, line.find("/"));
                    colorCounter++;
                } else if (colorCounter == 3){
                    substringBlue = line.substr(0, line.find("/"));
                    int red = stoi(substringRed);
                    int green = stoi(substringGreen);
                    int blue = stoi(substringBlue);
                    matrix->setColor(Color(red,green,blue),i,j);
                    colorCounter = 1;
                    j++;
                }
                line = line.substr(line.find("/") + 1);
            }
        }
        i++;
    }
    matrixToLoad.close();
}

void VentanaPrincipal::loadToFile()
{
    autoSavedCursor++;
    /*if (autoSavedCursor == 0){
        autoSavedCursor = 1;
    }*/
    ofstream matrixToSave ("autosave/slot"+to_string(autoSavedCursor)+".txt", ios::out | ios::trunc);
    for (int i = 0; i < matrix->getHeight(); i++)
    {
        for (int j = 0; j < matrix->getWidth(); j++)
        {
            matrixToSave << to_string((int)matrix->getColor(i,j).r)+"/"+to_string((int)matrix->getColor(i,j).g)+"/"+to_string((int)matrix->getColor(i,j).b)+"/";
        }
        matrixToSave << "\n";
    }
    matrixToSave.close();
    cout<<autoSavedCursor<<endl;
    autoSavedFlag++;
    //autoSavedCursor++;
    if (autoSavedCursor > 20){
        autoSavedCursor = 1;
    }
}

void VentanaPrincipal::on_actionSalir_triggered()
{
    unselectMagic();
    this->close();
}

void VentanaPrincipal::on_actionLapiz_triggered()
{
    instruction = PENCIL;
}

void VentanaPrincipal::on_actionColor_triggered()
{
    defaultColor = QColorDialog::getColor(Qt::black, this, "Color de lapiz");
}

void VentanaPrincipal::on_actionGrosor_triggered()
{
    lineWidth = QInputDialog::getInt(this,"lineWidth","Ingrese el lineWidth deseado",5,1,25);
}

void VentanaPrincipal::on_actionBorrador_triggered()
{
    instruction = TRACEERASER;
}

void VentanaPrincipal::on_actionBorrador_Figura_triggered()
{
    instruction = FIGUREERASER;
}

void VentanaPrincipal::on_actionCuadrado_triggered()
{
    instruction = SQUARE;
}

void VentanaPrincipal::on_actionRectangulo_triggered()
{
    instruction = RECTANGLE;
  }

void VentanaPrincipal::on_actionRombo_triggered()
{
    instruction = RHOMBUS;
}

void VentanaPrincipal::on_actionLinea_triggered()
{
    instruction = LINE;
}

void VentanaPrincipal::on_actionTriangulo_Escaleno_triggered()
{
    triangleCounter = 0;
    instruction = ESC;
}

void VentanaPrincipal::on_actionTriangulo_Isoceles_triggered()
{
    instruction = ISO;
}

void VentanaPrincipal::on_actionTriangulo_Rectangulo_triggered()
{
    instruction = REC;
}

void VentanaPrincipal::on_actionCirculo_triggered()
{
    instruction = CIRCLE;
}

void VentanaPrincipal::on_actionElipse_triggered()
{
    instruction = ELIPSE;
}

void VentanaPrincipal::on_actionSepia_triggered()
{
    unselectMagic();
    matrix->sepiaFilter();
    updateCanvas();
    update();
    loadToFile();
}

void VentanaPrincipal::on_actionEscala_de_grises_triggered()
{
    unselectMagic();
    matrix->grayScaleFilter();
    updateCanvas();
    update();
    loadToFile();
}


void VentanaPrincipal::on_actionBayer_triggered()
{
    unselectMagic();
    matrix->bayerFilter();
    updateCanvas();
    update();
    loadToFile();
}


void VentanaPrincipal::on_actionNegativo_triggered()
{
    unselectMagic();
    matrix->negativeFilter();
    updateCanvas();
    update();
    loadToFile();
}

void VentanaPrincipal::on_actionPickear_Color_triggered()
{
    instruction = PICKER;
}

void VentanaPrincipal::on_actionRellenar_triggered()
{
    instruction = PAINTFILL;
}

void VentanaPrincipal::on_actionFlip_Horizontal_triggered()
{
    unselectMagic();
    matrix->flipHorizontal();
    updateCanvas();
    update();
    loadToFile();

}

void VentanaPrincipal::on_actionFlip_Vertical_triggered()
{
    unselectMagic();
    matrix->flipVertical();
    updateCanvas();
    update();
    loadToFile();
}

void VentanaPrincipal::on_actionRotar_a_la_izquierda_triggered()
{
    unselectMagic();
    rotateLeft();
    updateSize();
    updateCanvas();
    update();
    loadToFile();
}

void VentanaPrincipal::on_actionRotar_a_la_derecha_triggered()
{
    rotateRight();
    updateSize();
    updateCanvas();
    update();
    loadToFile();
}

void VentanaPrincipal::on_actionSelect_Rectangulo_triggered()
{
    instruction = SELECTREC;
}

void VentanaPrincipal::on_actionSelect_Libre_triggered()
{
    instruction = SELECTFREE;
}

void VentanaPrincipal::on_actionSelect_Magico_triggered()
{
    instruction = SELECTMAGIC;
}


void VentanaPrincipal::on_actionDeshacer_triggered()
{
    if (autoSavedFlag != 0 && abs(autoSavedMoves) < autoSavedFlag){
        cout<<autoSavedFlag<<" "<<autoSavedMoves<<" "<<endl;
        autoSavedCursor--;
        autoSavedMoves--;
        if (autoSavedCursor < 0){
            autoSavedCursor = 20;
        }
        loadFromFile();
    }
    updateCanvas();
    update();
}

void VentanaPrincipal::on_actionRehacer_triggered()
{
    if (autoSavedFlag != 0 && autoSavedMoves < 0){
        autoSavedCursor++;
        autoSavedMoves++;
        if (autoSavedCursor > 20){
            autoSavedCursor = 1;
        }
        loadFromFile();
    }
    updateCanvas();
    update();
}

void VentanaPrincipal::on_horizontalSlider_sliderReleased()
{
    if(sizeFactor >= 2){
        zoomIn(sizeFactor);
        instruction = ZOOMIN;
    } else {
        updateCanvas();
        update();
    }
}

void VentanaPrincipal::on_horizontalSlider_valueChanged(int value)
{
    sizeFactor = value;
}
