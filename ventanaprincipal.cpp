#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"
#include "imageMatrix.h"
#include "Bitmap.h"
//#include <QDesktopWidget>
#include <QColorDialog>
#include <QInputDialog>
#include <ostream>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>

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

void VentanaPrincipal::iniciarComponentes(){
    elpixmap = new QPixmap(getAnchoLienzo(),getAltoLienzo());
    elpainter = new QPainter(elpixmap);
    pincelactivo = false;
    this->matrix = new imageMatrix(getAnchoLienzo(),getAltoLienzo());
    matrix->generateDefaultImage();
    elcolor = QColor(Qt::white);
    //actualizarLienzo();
    grosor = 2;
    codigoaccion = 0;
    nombreaccion = "";
    dibujarcuadrado = false;
    dibujarpixel = true;
}

/*void VentanaPrincipal::actualizarLienzo(){
    for(int fila = 0;fila<=getAltoLienzo();fila++){
        for(int columna = 0; columna<=getAnchoLienzo(); columna++){
           // elcolor = QColor(matrix->getColor(fila,columna).r,matrix->getColor(fila,columna).g,matrix->getColor(fila,columna).b);
            elpainter->setPen(QPen(elcolor));
            elpainter->drawPoint(QPoint(columna,fila));

        }
    }
}*/

void VentanaPrincipal::updateCanvas(){
    for (int i = 0; i < matrix->getHeight(); i++)
    {
        for (int j = 0; j < matrix->getWidth(); j++)
        {
            elpainter->setPen(QPen(QColor(matrix->getColor(i,j).r,matrix->getColor(i,j).g,matrix->getColor(i,j).b)));
            elpainter->drawPoint(QPoint(i,j));
            //Color colorTemp = getColor(i, j);
            //float formula = 0.3 * colorTemp.r + 0.59 * colorTemp.g + 0.11 * colorTemp.b;
            //setColor(Color(formula, formula, formula), i, j);
        }
    }
}

void VentanaPrincipal::actualizarTamano(){
    //Ajusta el tamaño de la ventana, en su posición "x" y "y", con el ancho del lienzo y
    //el alto del lienzo mas 50 pixeles donde se pondrán los botones de los controladores
    this->setGeometry(this->geometry().x(),this->geometry().y(),this->getAnchoLienzo(),this->getAltoLienzo()+50);
    this->ui->lblAlto->setText(QString::number(this->getAltoLienzo()));
    this->ui->lblAncho->setText(QString::number(this->getAnchoLienzo()));

}

void VentanaPrincipal::rotar(){
    int altotemp = altoLienzo;
    setAltolienzo(anchoLienzo);
    setAnchoLienzo(altotemp);
}
/*
void VentanaPrincipal::accionPintar(){
    if(dibujarcuadrado){
        pintarCuadrado();
    }
    if else {

    }



    }d::cout<<"La accion es "<<accion<<std::endl;
    switch(accion)
}*/

/*void VentanaPrincipal::pintarCuadrado(){

    matrix->square(Color(elcolor.red(),elcolor.green(),elcolor.blue()),puntoinicio.x(),puntoinicio.y(),puntofinal.x(),puntofinal.y(),grosor);
    int y1=  puntoinicio.y();
    int x1=  puntoinicio.x();
    int y2=  puntofinal.y();
    int x2=  puntofinal.y();
    std::cout<<"Aqui esta el error"<<std::endl;
    int diferentialx = x2 - x1;
    int diferentialy = y2 - y1;
    int lenghtx = fmin(abs(diferentialx), abs(diferentialy));
    int lenghty = lenghtx;
    if (diferentialx < 0)
    {
        lenghtx = lenghtx * -1;
    }
    if (diferentialy < 0)
    {
        lenghty = lenghty * -1;
    }
    QPen ellapiz = QPen(elcolor);
    ellapiz.setWidth(grosor);
    elpainter->setPen(ellapiz);
    elpainter->drawLine( y1, x1, y1, x1 + lenghtx);
    elpainter->drawLine(y1, x1, y1 + lenghty, x1);
    elpainter->drawLine(y1 + lenghty, x1, y1 + lenghty, x1 + lenghtx);
    elpainter->drawLine(y1, x1 + lenghtx, y1 + lenghty, x1 + lenghtx);
    //updateCanvas();
    update();
    elpainter->drawLine(puntoinicio.x(),puntoinicio.y(),puntofinal.x(),puntoinicio.y());
    elpainter->drawLine(puntoinicio.x(),puntoinicio.y(),puntoinicio.x(),puntofinal.y());
    elpainter->drawLine(puntoinicio.x(),puntofinal.y(),puntofinal.x(),puntofinal.y());
    elpainter->drawLine(puntofinal.x(),puntoinicio.y(),puntofinal.x(),puntofinal.y());
    update();

}*/

void VentanaPrincipal::mousePressEvent(QMouseEvent *event){
    if(0<=event->pos().x()&&event->pos().x()<=getAnchoLienzo()&&0<=event->pos().y()&&event->pos().y()<=getAltoLienzo()){
        puntoinicio = QPoint(event->pos().x(),event->pos().y()-70);
        std::cout<<"Se clickeo el boton en las coordenadas "<<puntoinicio.x()<<","<<puntoinicio.y()<<std::endl;
    }
    if(pincelactivo){
        std::cout<<"Se va a dibujar un pixel en "<<puntoinicio.x()<<","<<puntoinicio.y()<<std::endl;;
    }

    }

void VentanaPrincipal::mouseMoveEvent(QMouseEvent *event){
    if(0<=event->pos().x()&&event->pos().x()<=getAnchoLienzo()&&50<=event->pos().y()&&event->pos().y()<=getAltoLienzo()&&codigoaccion==1){
        puntofinal = QPoint(event->pos().x(),event->pos().y()-70);
        std::cout<<"Se va a dibujar un pixel en "<<puntofinal.x()<<","<<puntofinal.y()<<std::endl;;        
        QPen ellapiz(elcolor);
        ellapiz.setWidth(grosor);
        elpainter->setPen(ellapiz);
        elpainter->drawPoint(puntofinal.x(),puntofinal.y());
        matrix->pencil(Color(elcolor.red(),elcolor.green(),elcolor.blue()),puntofinal.y(),puntofinal.x(),grosor);
        update();
        event->accept();
    }

}

void VentanaPrincipal::mouseReleaseEvent(QMouseEvent *event){
    /*if(0<=event->pos().x()&&event->pos().x()<=getAnchoLienzo()&&0<=event->pos().y()&&event->pos().y()<=getAltoLienzo()){
        puntofinal = QPoint(event->pos().x(),event->pos().y()-70);
        std::cout<<"Se dejo de clickear el boton en las coordenadas"<<puntofinal.x()<<","<<puntofinal.y()<<std::endl;
    }*/
   //accionPintar();
}

void VentanaPrincipal::paintEvent(QPaintEvent *event){
    QPainter pintor = QPainter(this);
    pintor.drawPixmap(0,70, *elpixmap);
    event->accept();
}

int VentanaPrincipal::getAltoLienzo(){
    return this->altoLienzo;
}

void VentanaPrincipal::setAltolienzo(int _altolienzo){
    this->altoLienzo = _altolienzo;
}

int VentanaPrincipal::getAnchoLienzo(){
    return this->anchoLienzo;
}

void VentanaPrincipal::setAnchoLienzo(int _ancholienzo){
    this->anchoLienzo = _ancholienzo;
}

void VentanaPrincipal::on_actionColor_triggered()
{
    elcolor = QColorDialog::getColor(Qt::black, this, "Color de lapiz");
}


void VentanaPrincipal::on_actionLapiz_triggered()
{
    codigoaccion = 1;
    std::cout<<"Se va a usar el lapiz"<<std::endl;
    nombreaccion = "lapiz";
    this->ui->label->setText(nombreaccion);
}


void VentanaPrincipal::on_actionCuadrado_triggered()
{
    codigoaccion = 2;
    std::cout<<"Se va a hacer un cuadrado"<<std::endl;
    nombreaccion = "cuadrado";
    this->ui->label->setText(nombreaccion);
}


void VentanaPrincipal::on_actionSalir_triggered()
{
    this->close();
}


void VentanaPrincipal::on_actionRotar_a_la_izquierda_triggered()
{
    rotar();
    actualizarTamano();
}


void VentanaPrincipal::on_actionRotar_a_la_derecha_triggered()
{
    rotar();
    actualizarTamano();
}


void VentanaPrincipal::on_actionLinea_triggered()
{

}


void VentanaPrincipal::on_actionGrosor_triggered()
{
    grosor = QInputDialog::getInt(this,"grosor","Ingrese el grosor deseado",5,1,50);
}


void VentanaPrincipal::on_actionGuardar_Imagen_triggered()
{
    QString elnombre = QInputDialog::getText(this,"Nombre del bmp","Ingrese un nombre para el bmp");
    matrix->generatePixelArray();
    int size = matrix->getPixelArraySize();
    elbitmap = new Bitmap(elnombre.toStdString(),matrix->getWidth(),matrix->getHeight(), matrix->getPixelArray(), size);

}

