#pragma once

#include <QMainWindow>
#include <memory>
#include <canvas.h>
#include <QMdiArea>


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
     void set_mdiare ();

private:
    unique_ptr<impl_sheetflow_main> imp;

};

