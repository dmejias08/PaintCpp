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

#define PENCIL      1
#define SQUARE      2
#define RECTANGLE   3
#define ESC         4
#define ISO         5
#define REC         6
#define CIRCLE      7
#define ELIPSE      8
#define LINE        9
#define RHOMBUS     10
#define PAINTFILL   11
#define MAGICSEL    12
#define RECSEL      13
#define FREESEL     14
#define PICKER      15
#define BAYERFILTER 16
#define SEPIAFILTER 17
#define NEGATIVE    18
#define GRAY        19

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
    painter = new QPainter(canvasPixmap);
    this->matrix = new imageMatrix(getCanvasWidth(),getCanvasHeight());
    matrix->generateDefaultImage();
    defaultColor = QColor(Qt::black);
    defaultCanvasColor();
    lineWidth = 2;
    instruction = 0;
    stringAction = "";

}

void VentanaPrincipal::defaultCanvasColor(){
    for(int fila = 0;fila<=getCanvasHeight();fila++){
        for(int columna = 0; columna<=getCanvasWidth(); columna++){
            painter->setPen(QPen(QColor(Qt::white)));
            painter->drawPoint(QPoint(columna,fila));
        }
    }
}

void VentanaPrincipal::updateCanvas(){
    for (int i = 0; i < matrix->getHeight(); i++)
    {
        for (int j = 0; j < matrix->getWidth(); j++)
        {
            painter->setPen(QPen(QColor(matrix->getColor(i,j).r,matrix->getColor(i,j).g,matrix->getColor(i,j).b)));
            painter->drawPoint(QPoint(j,i));
        }
    }
}

void VentanaPrincipal::updateSize(){
    //Ajusta el tamaño de la ventana, en su posición "x" y "y", con el ancho del lienzo y
    //el alto del lienzo mas 70 pixeles donde se pondrán los botones de los controladores
    this->setGeometry(this->geometry().x(),this->geometry().y(),this->getCanvasWidth(),this->getCanvasHeight()+70);
    this->ui->lblAlto->setText(QString::number(this->getCanvasHeight()));
    this->ui->lblAncho->setText(QString::number(this->getCanvasWidth()));

}

void VentanaPrincipal::rotateRight(){
    int altotemp = canvasHeight;
    setCanvasHeight(canvasWidth);
    setCanvasWidth(altotemp);
    matrix->rotate();
    matrix->rotate();
    matrix->rotate();
    canvasPixmap = new QPixmap(getCanvasWidth(),getCanvasHeight());
    painter = new QPainter(canvasPixmap);
    updateCanvas();
    updateSize();
}

void VentanaPrincipal::rotateLeft(){
    int altotemp = canvasHeight;
    setCanvasHeight(canvasWidth);
    setCanvasWidth(altotemp);
    matrix->rotate();
    canvasPixmap = new QPixmap(getCanvasWidth(),getCanvasHeight());
    painter = new QPainter(canvasPixmap);
    updateCanvas();
    updateSize();
}

void VentanaPrincipal::actionPointPressed(){
    switch (instruction) {
    case PAINTFILL:
        paintFill();
        break;
    case PICKER:
        pickColor();
    case ESC:
        paintTriangleESC();
    default:
        break;
    }
}


void VentanaPrincipal::actionButtonPressed(){
    switch (instruction) {
    case SQUARE:
        paintSquare();
        break;
    case RECTANGLE:
        paintRectangle();
        break;
    case ISO:
        paintTriangleISO();
        break;
    case REC:
        paintTriangleREC();
        break;
    case LINE:
        paintLine();
        break;
    case CIRCLE:
        paintCircle();
        break;
    case ELIPSE:
        paintElipse();
        break;
    case RHOMBUS:
        paintRhombus();
        break;
    case BAYERFILTER:
        bayerFilter();
        break;
    case SEPIAFILTER:
        sepiaFilter();
        break;
    case NEGATIVE:
        negative();
        break;
    case GRAY:
        gray();
        break;
    default:
        break;
    }
}

void VentanaPrincipal::paintSquare(){

    matrix->square(Color(defaultColor.red(),defaultColor.green(),defaultColor.blue()),startPoint.x(),startPoint.y(),endPoint.x(),endPoint.y(),lineWidth);
    updateCanvas();
    update();

}

void VentanaPrincipal::paintRectangle(){
    matrix->rectangle(Color(defaultColor.red(),defaultColor.green(),defaultColor.blue()),startPoint.x(),startPoint.y(),endPoint.x(),endPoint.y(),lineWidth);
    updateCanvas();
    update();
}

void VentanaPrincipal::paintTriangleESC(){
    triangleCounter++;
    if (triangleCounter == 1){
        firstPoint = startPoint;
    } else if (triangleCounter == 2) {
        secondPoint = startPoint;
    } else if (triangleCounter == 3){
        thirdPoint = startPoint;
        matrix->triangleEsc(Color(defaultColor.red(),defaultColor.green(),defaultColor.blue()),firstPoint.x(),firstPoint.y(),secondPoint.x(),secondPoint.y(),thirdPoint.x(),thirdPoint.y(),lineWidth);
        triangleCounter = 0;
        updateCanvas();
        update();
    }

}

void VentanaPrincipal::paintTriangleISO(){
    matrix->triangleIso(Color(defaultColor.red(),defaultColor.green(),defaultColor.blue()),startPoint.x(),startPoint.y(),endPoint.x(),endPoint.y(),lineWidth);
    updateCanvas();
    update();
}

void VentanaPrincipal::paintTriangleREC(){
    matrix->triangleRec(Color(defaultColor.red(),defaultColor.green(),defaultColor.blue()),startPoint.x(),startPoint.y(),endPoint.x(),endPoint.y(),lineWidth);
    updateCanvas();
    update();
}

void VentanaPrincipal::paintRhombus(){
    matrix->rhombus(Color(defaultColor.red(),defaultColor.green(),defaultColor.blue()),startPoint.x(),startPoint.y(),endPoint.x(),endPoint.y(),lineWidth);
    updateCanvas();
    update();
}

void VentanaPrincipal::paintCircle(){
    matrix->circle(Color(defaultColor.red(),defaultColor.green(),defaultColor.blue()),startPoint.x(),startPoint.y(),endPoint.x(),endPoint.y(), lineWidth);
    updateCanvas();
    update();
}

void VentanaPrincipal::paintElipse(){
    matrix->elipse(Color(defaultColor.red(),defaultColor.green(),defaultColor.blue()),startPoint.x(),startPoint.y(),endPoint.x(),endPoint.y(), lineWidth);
    updateCanvas();
    update();
}

void VentanaPrincipal::paintLine(){
    matrix->line(Color(defaultColor.red(),defaultColor.green(),defaultColor.blue()),startPoint.y(),startPoint.x(),endPoint.y(),endPoint.x(), lineWidth);
    updateCanvas();
    update();
}

void VentanaPrincipal::paintFill(){
   matrix->paintFill(matrix->getColor(startPoint.y(),startPoint.x()),Color(defaultColor.red(),defaultColor.green(),defaultColor.blue()),startPoint.x(),startPoint.y());
   updateCanvas();
   update();
}

void VentanaPrincipal::pickColor(){
    Color temp = matrix->getColor(startPoint.y(),startPoint.x());
    defaultColor.setRed(temp.r);
    defaultColor.setGreen(temp.g);
    defaultColor.setBlue(temp.b);
}
void VentanaPrincipal::bayerFilter(){
    matrix->bayerFilter();
    updateCanvas();
    update();
}
void VentanaPrincipal::sepiaFilter(){
    matrix->sepiaFilter();
    updateCanvas();
    update();

}
void VentanaPrincipal::negative(){
    matrix->negativeFilter();
    updateCanvas();
    update();

}
void VentanaPrincipal::gray(){
    matrix->grayScaleFilter();
    updateCanvas();
    update();
}

void VentanaPrincipal::mousePressEvent(QMouseEvent *event){
    if(0 <= event->pos().x() && event->pos().x() < getCanvasWidth() && 70 < event->pos().y() && event->pos().y() < getCanvasHeight()+70){
        startPoint = QPoint(event->pos().x(),event->pos().y()-70);
        std::cout<<"Se clickeo el boton en las coordenadas "<<startPoint.x()<<","<<startPoint.y()<<std::endl;
        actionPointPressed();
    }
}

void VentanaPrincipal::mouseMoveEvent(QMouseEvent *event){
    try {
        if(0 <= event->pos().x() && event->pos().x() < getCanvasWidth() && 70 < event->pos().y() && event->pos().y() < getCanvasHeight()+70 && instruction==1){
            endPoint = QPoint(event->pos().x(),event->pos().y()-70);
            std::cout<<"Se va a dibujar un pixel en "<<endPoint.x()<<","<<endPoint.y()<<std::endl;;
            QPen ellapiz(defaultColor);
            ellapiz.setWidth(lineWidth);
            painter->setPen(ellapiz);
            painter->drawPoint(endPoint.x(),endPoint.y());
            matrix->pencil(Color(defaultColor.red(),defaultColor.green(),defaultColor.blue()),endPoint.y()-1,endPoint.x(),lineWidth);
            update();
            event->accept();
        }
    } catch (...) {
    }
}

void VentanaPrincipal::mouseReleaseEvent(QMouseEvent *event){
    if(0 <= event->pos().x() && event->pos().x() < getCanvasWidth() && 70 < event->pos().y() && event->pos().y() < getCanvasHeight()+70){
        endPoint = QPoint(event->pos().x(),event->pos().y()-70);
        std::cout<<"Se dejo de clickear el boton en las coordenadas"<<endPoint.x()<<","<<endPoint.y()<<std::endl;
        actionButtonPressed();
    }

}

void VentanaPrincipal::paintEvent(QPaintEvent *event){
    QPainter *pintor = new QPainter(this);
    pintor->drawPixmap(0,70, *canvasPixmap);
    event->accept();
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
    //QString elnombre = QInputDialog::getText(this,"Nombre del bmp","Ingrese un nombre para el bmp");
    std::cout<<elnombre.toStdString()<<std::endl;
    matrix->generatePixelArray();
    int size = matrix->getPixelArraySize();
    canvasBitmap = new Bitmap(elnombre.toStdString(),matrix->getWidth(),matrix->getHeight(), matrix->getPixelArray(), size);

}

void VentanaPrincipal::on_actionCargar_Imagen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Abrir bmp","C://","Bmp file (*.bmp)");
    std::cout<<filename.toStdString()<<std::endl;
    canvasBitmap = new Bitmap(filename.toStdString());
    canvasHeight = canvasBitmap->getHeight();
    canvasWidth = canvasBitmap->getWidth();
    setCanvasHeight(canvasHeight);
    setCanvasWidth(canvasWidth);
    this->matrix = new imageMatrix(canvasBitmap->getArray(),canvasHeight, canvasWidth);
    canvasPixmap = new QPixmap(getCanvasWidth(),getCanvasHeight());
    painter = new QPainter(canvasPixmap);
    updateCanvas();
    updateSize();
    //filename.toStdString(); para convertirlo a string
}

void VentanaPrincipal::on_actionSalir_triggered()
{
    this->close();
}

void VentanaPrincipal::on_actionLapiz_triggered()
{
    instruction = PENCIL;
    std::cout<<"Se va a usar el lapiz"<<std::endl;
    stringAction = "Lapiz";
    this->ui->label->setText(stringAction);
}

void VentanaPrincipal::on_actionColor_triggered()
{
    defaultColor = QColorDialog::getColor(Qt::black, this, "Color de lapiz");
}

void VentanaPrincipal::on_actionGrosor_triggered()
{
    lineWidth = QInputDialog::getInt(this,"lineWidth","Ingrese el lineWidth deseado",5,1,50);
}

void VentanaPrincipal::on_actionBorrador_triggered()
{

}

void VentanaPrincipal::on_actionBorrador_Figura_triggered()
{

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

}

void VentanaPrincipal::on_actionEscala_de_grises_triggered()
{

}


void VentanaPrincipal::on_actionBayer_triggered()
{

}


void VentanaPrincipal::on_actionNegativo_triggered()
{

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
    matrix->flipHorizontal();
    updateCanvas();
    update();

}

void VentanaPrincipal::on_actionFlip_Vertical_triggered()
{
    matrix->flipVertical();
    updateCanvas();
    update();
}

void VentanaPrincipal::on_actionRotar_a_la_izquierda_triggered()
{
    rotateLeft();
    updateSize();
}

void VentanaPrincipal::on_actionRotar_a_la_derecha_triggered()
{
    rotateRight();
    updateSize();
}

void VentanaPrincipal::on_actionSelect_Rectangulo_triggered()
{

}

void VentanaPrincipal::on_actionSelect_Libre_triggered()
{

}

void VentanaPrincipal::on_actionSelect_Magico_triggered()
{

}

void VentanaPrincipal::on_actionZoom_in_triggered()
{

}

void VentanaPrincipal::on_actionZoom_out_triggered()
{

}

void VentanaPrincipal::on_actionDeshacer_triggered()
{

}

void VentanaPrincipal::on_actionRehacer_triggered()
{

}



