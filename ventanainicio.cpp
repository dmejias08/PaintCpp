#include "ventanainicio.h"
#include "./ui_ventanainicio.h"
#include "ventanaprincipal.h"
#include <QMessageBox>

VentanaInicio::VentanaInicio(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VentanaInicio)
{
    ui->setupUi(this);
}

VentanaInicio::~VentanaInicio()
{
    delete ui;
}


void VentanaInicio::on_pushButton_clicked()
{
    if(!validarEntrada()){
        QMessageBox::information(this,"Error", "El valor agregado no es numero");
    }else if(!validarTamanoEntrada()){
        QMessageBox::information(this,"Error", "El valor agregado exede el rango permitido");
    }else{
        VentanaPrincipal *laventanaprincipal = new VentanaPrincipal(this);
        laventanaprincipal->isModal();
        laventanaprincipal->setVisible(true);
        laventanaprincipal->setCanvasHeight(this->obtenerAlto());
        laventanaprincipal->setCanvasWidth(this->obtenerAncho());
        laventanaprincipal->startComponents();
        laventanaprincipal->updateSize();
        this->hide();
    }
}

/*
 * Metodo para obtener el ancho introducido por el usuario
 */
int VentanaInicio::obtenerAncho(){
    return this->ui->txtAncho->text().toInt();
}
/*
 * Metodo para obtener el alto introducido por el usuario
 */
int VentanaInicio::obtenerAlto(){
    return this->ui->txtAlto->text().toInt();
}

bool VentanaInicio::validarEntrada(){
    if(this->ui->txtAlto->text().toInt()&&this->ui->txtAncho->text().toInt()){
        return true;
    }
    return false;
}
bool VentanaInicio::validarTamanoEntrada(){
    if(0<obtenerAlto()&&obtenerAlto()<=1280&&0<obtenerAncho()&&obtenerAncho()<=1280){
        return true;
    }
    return false;
}
