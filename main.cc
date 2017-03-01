#include "sheetflow_main.h"
#include <QApplication>
#include "drag_widget.h"
#include <vector>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::vector<QString>  names = {"原材料", "加工", "检验", "产成品", "连线1", "连线2"};
    auto wm = sheetflow_main::make();
    auto w = drag_widget::make(names);

    w->show ();
    wm->show();
    return a.exec();
}
