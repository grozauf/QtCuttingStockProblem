#include "QtCuttingStockProblem.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtCuttingStockProblem w;
    w.show();
    return a.exec();
}
