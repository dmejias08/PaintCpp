#include "ventanainicio.h"
#include "./ui_ventanainicio.h"
#include "ventanaprincipal.h"

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
    VentanaPrincipal *laventanaprincipal = new VentanaPrincipal(this);
    laventanaprincipal->isModal();
    laventanaprincipal->setVisible(true);
    laventanaprincipal->setCanvasHeight(this->obtenerAlto());
    laventanaprincipal->setCanvasWidth(this->obtenerAncho());
    laventanaprincipal->startComponents();
    laventanaprincipal->updateSize();
    this->hide();
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

