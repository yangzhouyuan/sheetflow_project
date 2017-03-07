#include "sheetflow_main.h"
#include <QApplication>
#include "drag_widget.h"
#include <vector>
#include "canvas_scene.h"
#include "canvas_view.h"
#include "item/raw_material.h"
#include "item/machining.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    qDebug () << "123";
    QApplication a(argc, argv);

    auto wm = sheetflow_main::make();

    wm->show();
    return a.exec();
}
