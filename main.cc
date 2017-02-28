#include "sheetflow_main.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto w = sheetflow_main::make();
    w->show ();
    return a.exec();
}
