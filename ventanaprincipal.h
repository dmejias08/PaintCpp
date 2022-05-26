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

    void on_horizontalSlider_sliderReleased();

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::VentanaPrincipal *ui;
    int canvasHeight;
    int canvasWidth;
    int sizeFactor = 1;
    int memoryFlag = 0;
    int autoSavedCursor = 0;
    int autoSavedFlag = 0;
    int autoSavedMoves = 0;
    bool selectON = false;
    bool selectOFF = false;
    QColor defaultColor;
    QColor afterEraser;
    QPoint startPoint;
    QPoint firstPoint;
    QPoint secondPoint;
    QPoint thirdPoint;
    QPoint endPoint;
    QPoint lastPoint;
    QPoint selectPoint;
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
    void paintPencil(QColor colorToUse);
    void paintSquare(QColor colorToUse);
    void paintRectangle(QColor colorToUse);
    void paintTriangleESC(QColor colorToUse);
    void paintTriangleISO(QColor colorToUse);
    void paintTriangleREC(QColor colorToUse);
    void paintRhombus(QColor colorToUse);
    void paintCircle(QColor colorToUse);
    void paintElipse(QColor colorToUse);
    void paintLine(QColor colorToUse);
    void paintFill(QColor colorToUse, int x1, int y1);
    void zoomIn(int sizeFactor);
    void selectRectangle(int x1, int y1, int x2, int y2);
    void selectFree();
    void loadFromFile();
    void loadToFile();
    void pickColor();
    void updateCanvas();
    void unselectMagic();

};

#endif // VENTANAPRINCIPAL_H

