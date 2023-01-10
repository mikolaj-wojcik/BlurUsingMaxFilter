#include "JABlur.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JABlur w;
    w.show();
    return a.exec();
}
