#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

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


private slots:
    void on_actionColor_triggered();

    void on_actionLapiz_triggered();

    void on_actionCuadrado_triggered();

    void on_actionSalir_triggered();

private:
    Ui::VentanaPrincipal *ui;
    int altoLienzo;
    int anchoLienzo;
    QColor elcolor;
};

#endif // VENTANAPRINCIPAL_H
