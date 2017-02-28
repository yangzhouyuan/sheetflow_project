#ifndef SHEETFLOW_MAIN_H
#define SHEETFLOW_MAIN_H

#include <QMainWindow>
#include <QToolBar>

namespace Ui {
class sheetflow_main;
}

class sheetflow_main : public QMainWindow
{
    Q_OBJECT

public:
    explicit sheetflow_main(QWidget *parent = 0);
    ~sheetflow_main();
private:
    void create_toolbar ();


private:
    Ui::sheetflow_main *ui;
    QToolBar* file_toolbar_ = addToolBar("文件");
    QToolBar* window_toolbar_ = addToolBar("窗口");
    QToolBar* edit_toolbar_ = addToolBar("编辑");

};

#endif // SHEETFLOW_MAIN_H
