#include "sheetflow_main.h"
#include <QApplication>
#include "drag_widget.h"
#include <vector>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::vector<QString>  labels = {"加工", "检验", "产成品"};
    std::vector<QString> buttons = {"原材料", "连线1", "连线2"};

    auto w = drag_widget::make(labels, buttons);

    auto wm = sheetflow_main::make();

    w->show();
    wm->show();
    return a.exec();
}
