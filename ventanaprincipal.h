#include "imageMatrix.h"
#include "qpainter.h"
#ifndef VENTANAPRINCIPAL_H
//#define "ventanaprincipal.h"
#include <iostream>

#include <QMainWindow>

namespace Ui {
class VentanaPrincipal;
}

class VentanaPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    explicit VentanaPrincipal(QWidget *parent = nullptr);
    ~VentanaPrincipal();
    int getAltoLienzo();
    void setAltolienzo(int );
    int getAnchoLienzo();
    void setAnchoLienzo(int );
    void actualizarTamano();
    void iniciarComponentes();
    void actualizarLienzo();

protected:
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void paintEvent(QPaintEvent*) override;

private slots:
    void on_actionColor_triggered();

    void on_actionLapiz_triggered();

    void on_actionCuadrado_triggered();

    void on_actionSalir_triggered();

    void on_actionRotar_a_la_izquierda_triggered();

    void on_actionRotar_a_la_derecha_triggered();

    void on_actionLinea_triggered();

    void on_actionGrosor_triggered();

    void on_actionGuardar_Imagen_triggered();

private:
    Ui::VentanaPrincipal *ui;
    int altoLienzo;
    int anchoLienzo;
    QColor elcolor;
    QPoint puntoinicio;
    QPoint puntofinal;
    bool pincelactivo;
    bool cuadradoactivo;
    QPixmap *elpixmap;
    QPainter *elpainter;
    imageMatrix *matrix;
    int grosor;
    void rotar();
};

#endif // VENTANAPRINCIPAL_H
