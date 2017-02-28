#include "sheetflow_main.h"
#include <QApplication>
#include <QDebug>
#include "drag_widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    auto w = sheetflow_main::make();
    auto w = drag_widget::make();

    w->show ();

    return a.exec();
}
