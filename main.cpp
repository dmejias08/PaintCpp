#include "ventanainicio.h"

#include <QApplication>
#include "imageMatrix.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VentanaInicio w;
    w.show();
    return a.exec();
}
