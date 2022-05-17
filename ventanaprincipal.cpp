#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"
#include <QColorDialog>
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

void VentanaPrincipal::actualizarTamano(){
    //Ajusta el tamaño de la ventana, en su posición "x" y "y", con el ancho del lienzo y
    //el alto del lienzo mas 50 pixeles donde se pondrán los botones de los controladores
    this->setGeometry(this->geometry().x(),this->geometry().y(),this->getAnchoLienzo(),this->getAltoLienzo()+50);
    ui->lblAlto->setText(QString::number(this->getAltoLienzo()));
    ui->lblAncho->setText(QString::number(this->getAnchoLienzo()));

    //Ubica el frame en el punto 0 en "x" y 50 en "y" ya que en la parte superior van a estar los
    //controladores
    this->ui->frameLienzo->setGeometry(0,50,getAnchoLienzo(),getAltoLienzo());
    //Se rellena el frame con un color para diferenciarlo
    this->ui->frameLienzo->setStyleSheet("background-color: white");


}
void VentanaPrincipal::rotar(){
    int altotemp = altoLienzo;
    setAltolienzo(anchoLienzo);
    setAnchoLienzo(altotemp);
}

void VentanaPrincipal::mousePressEvent(QMouseEvent *event){
    if(0<=event->pos().x()&&event->pos().x()<=getAnchoLienzo()&&50<=event->pos().y()&&event->pos().y()<=getAltoLienzo()+50){
        puntoinicio = event->pos();
        std::cout<<"Se clickeo el boton en las coordenadas "<<puntoinicio.x()<<","<<puntoinicio.y()<<std::endl;
    }
    if(pincelactivo){
        std::cout<<"Se va a dibujar un pixel en "<<puntoinicio.x()<<","<<puntoinicio.y()<<std::endl;;
    }

    }

void VentanaPrincipal::mouseMoveEvent(QMouseEvent *event){
    if(0<=event->pos().x()&&event->pos().x()<=getAnchoLienzo()&&50<=event->pos().y()&&event->pos().y()<=getAltoLienzo()+50&&pincelactivo){
        puntofinal = event->pos();
        std::cout<<"Se va a dibujar un pixel en "<<puntofinal.x()<<","<<puntofinal.y()<<std::endl;;
        //std::cout<<"Se esta moviendo el boton en las coordenadas"<<puntofinal.x()<<","<<puntofinal.y()<<std::endl;
    }
    /*if(pincelactivo){
        std::cout<<"Se va a dibujar un pixel en "<<puntofinal.x()<<","<<puntofinal.y()<<std::endl;;
    }*/
}

void VentanaPrincipal::mouseReleaseEvent(QMouseEvent *event){
    if(0<=event->pos().x()&&event->pos().x()<=getAnchoLienzo()&&50<=event->pos().y()&&event->pos().y()<=getAltoLienzo()+50){
        puntofinal = event->pos();
        std::cout<<"Se dejo de clickear el boton en las coordenadas"<<puntofinal.x()<<","<<puntofinal.y()<<std::endl;
    }
    if(cuadradoactivo){
        std::cout<<"Se va a crear un cuadrado de "<<puntoinicio.x()<<","<<puntoinicio.y()<<" a "<<puntofinal.x()<<" , "<<puntofinal.y()<<std::endl;
    }
}

void VentanaPrincipal::paintEvent(QPaintEvent *event){
    QPainter pintor = QPainter(this);
    QPen lapiz;
    lapiz.setColor(QColor(0,0,0));
    pintor.drawLine(puntoinicio,puntoinicio);
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

