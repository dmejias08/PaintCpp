#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"
#include <QColorDialog>
#include <ostream>

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
    std::cout<<"Se va a usar la compu"<<std::endl;
}


void VentanaPrincipal::on_actionCuadrado_triggered()
{
    std::cout<<"Se va a hacer un cuadrado"<<std::endl;
}


void VentanaPrincipal::on_actionSalir_triggered()
{
    this->close();
}

