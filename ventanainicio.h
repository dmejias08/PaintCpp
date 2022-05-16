#ifndef VENTANAINICIO_H
#define VENTANAINICIO_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class VentanaInicio; }
QT_END_NAMESPACE

class VentanaInicio : public QMainWindow
{
    Q_OBJECT

public:
    VentanaInicio(QWidget *parent = nullptr);
    ~VentanaInicio();

private:
    Ui::VentanaInicio *ui;
};
#endif // VENTANAINICIO_H
