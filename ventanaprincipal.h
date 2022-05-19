#include "imageMatrix.h"
#include "qpainter.h"
#include "Bitmap.h"
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
    int getCanvasHeight();
    void setCanvasHeight(int );
    int getCanvasWidth();
    void setCanvasWidth(int );
    void updateSize();
    void startComponents();
    void defaultCanvasColor();

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

    void on_actionPickear_Color_triggered();

    void on_actionRellenar_triggered();

    void on_actionFlip_Horizontal_triggered();

    void on_actionFlip_Vertical_triggered();

    void on_actionDeshacer_triggered();

    void on_actionRehacer_triggered();

    void on_actionCargar_Imagen_triggered();

    void on_actionBorrador_triggered();

    void on_actionSelect_Rectangulo_triggered();

    void on_actionSelect_Libre_triggered();

    void on_actionSelect_Magico_triggered();

    void on_actionRectangulo_triggered();

    void on_actionTriangulo_Escaleno_triggered();

    void on_actionTriangulo_Isoceles_triggered();

    void on_actionRombo_triggered();

    void on_actionCirculo_triggered();

    void on_actionElipse_triggered();

    void on_actionTriangulo_Rectangulo_triggered();

    void on_actionBorrador_Figura_triggered();

    void on_actionSepia_triggered();

    void on_actionEscala_de_grises_triggered();

    void on_actionBayer_triggered();

    void on_actionNegativo_triggered();

    void on_actionZoom_out_triggered();

    void on_actionZoom_in_triggered();

private:
    Ui::VentanaPrincipal *ui;
    int canvasHeight;
    int canvasWidth;
    QColor defaultColor;
    QPoint startPoint;
    QPoint firstPoint;
    QPoint secondPoint;
    QPoint thirdPoint;
    QPoint endPoint;
    QPixmap *canvasPixmap;
    QPainter *painter;
    Bitmap *canvasBitmap;
    imageMatrix *matrix;
    int lineWidth;
    int instruction;
    int triangleCounter = 0;
    QString stringAction;
    void rotateRight();
    void rotateLeft();
    void actionButtonPressed();
    void actionPointPressed();
    void paintSquare();
    void paintRectangle();
    void paintTriangleESC();
    void paintTriangleISO();
    void paintTriangleREC();
    void paintRhombus();
    void paintCircle();
    void paintElipse();
    void paintLine();
    void paintFill();
    void pickColor();
    void updateCanvas();
};

#endif // VENTANAPRINCIPAL_H

