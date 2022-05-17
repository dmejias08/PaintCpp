#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"
#include "imageMatrix.h"
#include "Bitmap.h"
//#include <QDesktopWidget>
#include <QColorDialog>
#include <QDialog>
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
    actualizarLienzo();
    grosor = 2;
}

void VentanaPrincipal::actualizarLienzo(){
    for(int fila = 0;fila<=getAltoLienzo();fila++){
        for(int columna = 0; columna<=getAnchoLienzo(); columna++){
           // elcolor = QColor(matrix->getColor(fila,columna).r,matrix->getColor(fila,columna).g,matrix->getColor(fila,columna).b);
            elpainter->setPen(QPen(elcolor));
            elpainter->drawPoint(QPoint(columna,fila));

        }
    }
}
void VentanaPrincipal::actualizarTamano(){
    //Ajusta el tamaño de la ventana, en su posición "x" y "y", con el ancho del lienzo y
    //el alto del lienzo mas 50 pixeles donde se pondrán los botones de los controladores
    this->setGeometry(this->geometry().x(),this->geometry().y(),this->getAnchoLienzo(),this->getAltoLienzo()+50);
    this->ui->lblAlto->setText(QString::number(this->getAltoLienzo()));
    this->ui->lblAncho->setText(QString::number(this->getAnchoLienzo()));

    //Ubica el frame en el punto 0 en "x" y 50 en "y" ya que en la parte superior van a estar los
    //controladores
    //this->ui->frameLienzo->setGeometry(0,50,getAnchoLienzo(),getAltoLienzo());
    //Se rellena el frame con un color para diferenciarlo
    //this->ui->frameLienzo->setStyleSheet("background-color: white");



}
void VentanaPrincipal::rotar(){
    int altotemp = altoLienzo;
    setAltolienzo(anchoLienzo);
    setAnchoLienzo(altotemp);
}

void VentanaPrincipal::mousePressEvent(QMouseEvent *event){
    if(0<=event->pos().x()&&event->pos().x()<=getAnchoLienzo()&&0<=event->pos().y()&&event->pos().y()<=getAltoLienzo()){
        puntoinicio = event->pos();
        std::cout<<"Se clickeo el boton en las coordenadas "<<puntoinicio.x()<<","<<puntoinicio.y()<<std::endl;
    }
    if(pincelactivo){
        std::cout<<"Se va a dibujar un pixel en "<<puntoinicio.x()<<","<<puntoinicio.y()<<std::endl;;
    }

    }

void VentanaPrincipal::mouseMoveEvent(QMouseEvent *event){
    if(0<=event->pos().x()&&event->pos().x()<=getAnchoLienzo()&&50<=event->pos().y()&&event->pos().y()<=getAltoLienzo()&&pincelactivo){
        puntofinal = event->pos();
        std::cout<<"Se va a dibujar un pixel en "<<puntofinal.x()<<","<<puntofinal.y()<<std::endl;;        
        elpainter->setPen(QPen(elcolor));
        elpainter->drawPoint(puntofinal.x(),puntofinal.y()-70);

        matrix->pencil(Color(elcolor.red(),elcolor.green(),elcolor.blue()),puntofinal.y(),puntofinal.x(),grosor);
        update();
        event->accept();
    }

}

void VentanaPrincipal::mouseReleaseEvent(QMouseEvent *event){
    if(0<=event->pos().x()&&event->pos().x()<=getAnchoLienzo()&&0<=event->pos().y()&&event->pos().y()<=getAltoLienzo()){
        puntofinal = event->pos();
        std::cout<<"Se dejo de clickear el boton en las coordenadas"<<puntofinal.x()<<","<<puntofinal.y()<<std::endl;
    }
    if(cuadradoactivo){
        std::cout<<"Se va a crear un cuadrado de "<<puntoinicio.x()<<","<<puntoinicio.y()<<" a "<<puntofinal.x()<<" , "<<puntofinal.y()<<std::endl;
        matrix->square(Color(elcolor.red(),elcolor.green(),elcolor.blue()),puntoinicio.x(),puntoinicio.y(),puntofinal.x(),puntofinal.y(),4);
    }
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
    pincelactivo = true;
    std::cout<<"Se va a usar el lapiz"<<std::endl;
}


void VentanaPrincipal::on_actionCuadrado_triggered()
{
    pincelactivo = false;
    cuadradoactivo = true;
    std::cout<<"Se va a hacer un cuadrado"<<std::endl;
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

}


void VentanaPrincipal::on_actionGuardar_Imagen_triggered()
{
    matrix->generatePixelArray();
    int size = matrix->getPixelArraySize();
    Bitmap *xport = new Bitmap("prueba",matrix->getWidth(),matrix->getHeight(), matrix->getPixelArray(), size);

}

