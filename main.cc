#include "sheetflow_main.h"
#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    sheetflow_main w;
    w.show();
    qDebug() << "echo" ;
    return a.exec();
}
