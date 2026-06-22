#include "drawserver.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DrawServer w;
    w.show();
    return a.exec();
}
