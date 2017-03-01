#pragma once

#include <QMainWindow>
#include <memory>
#include <canvas.h>
#include <QMdiArea>
#include <QDockWidget>
#include <drag_widget.h>
using std::unique_ptr;

namespace Ui {
class sheetflow_main;
}

struct impl_sheetflow_main;

class sheetflow_main : public QMainWindow
{
    Q_OBJECT
public:
    ~sheetflow_main();
    static unique_ptr<sheetflow_main> make ();
    void file_new ();
protected:
    explicit sheetflow_main(QWidget *parent = 0);
    bool init ();
private:
    void create_toolbars ();
    void connections ();
    void create_actions ();
    canvas* create_canvas_body();
    void set_draw ();
    void set_mdiare ();
    void set_draw_widget_name ();
private:
    unique_ptr<impl_sheetflow_main> imp;
    std::unique_ptr<QDockWidget> drawer_ = std::make_unique<QDockWidget> (this);
    std::unique_ptr<drag_widget> draw_widget;



};

