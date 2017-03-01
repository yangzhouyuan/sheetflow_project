#include "sheetflow_main.h"
#include "ui_sheetflow_main.h"
#include <QToolBar>
#include <QMenu>
#include <QAction>
#include <QIcon>
#include <QToolBar>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <memory>
#include <QMdiSubWindow>
#include <QDebug>
struct impl_sheetflow_main
{
    QMenuBar* menu;
    QMenu* menu_file;
    QMenu* menu_window;
    QMenu* menu_edit;

    QToolBar* toolbar_file;
    QToolBar* toolbar_window ;
    QToolBar* toolbar_edit ;

    QAction* action_file_new;
    QAction* action_file_open ;
    QAction* action_file_save ;
    QAction* action_file_other_save ;
    QAction* action_print ;

    QAction* action_draw ;
    QAction* action_zoom_in;
    QAction* action_zoom_out;

    QMdiArea* mdiare = new QMdiArea();
};

sheetflow_main::sheetflow_main(QWidget *parent) :
    QMainWindow(parent)
{

}

bool sheetflow_main::init()
{

    create_actions ();
    set_mdiare();
    create_toolbars ();
    connections ();
    return true;
}

sheetflow_main::~sheetflow_main()
{
}

unique_ptr<sheetflow_main> sheetflow_main::make()
{
    unique_ptr<sheetflow_main> ret (new sheetflow_main);
    if (ret == nullptr or ! ret->init ())
    {
        return nullptr;
    }

    return ret;
}

void sheetflow_main::file_new()
{
    canvas* canva = create_canvas_body();
    canva->show();
}



void sheetflow_main::connections()
{
    connect( imp->action_file_new, &QAction::triggered, this, &sheetflow_main::file_new);
}

void sheetflow_main::create_actions()
{
    imp = std::make_unique<impl_sheetflow_main>();
    imp->menu = new QMenuBar(this);
    this->setMenuBar(imp->menu);

    imp->menu_file = new QMenu("文件",this);
    imp->menu_window = new QMenu("窗口",this);
    imp->menu_edit = new QMenu("编辑",this);


    imp->menu->addMenu(imp->menu_file);
    imp->menu->addMenu(imp->menu_window);
    imp->menu->addMenu(imp->menu_edit);

    imp->action_file_new = new QAction(QIcon("./image/filenew.png"),"新建",this);
    imp->action_file_open = new QAction(QIcon("./image/fileopen.png"),"打开",this);
    imp->action_file_save = new QAction(QIcon("./image/filesave.png"),"保存",this);
    imp->action_file_other_save = new QAction(QIcon("./image/fileother_save.png"),"另存为",this);
    imp->action_print = new QAction(QIcon("./image/print.png"),"打印",this);

    imp->action_draw = new QAction(QIcon("./image/show_drawer.png"),"抽屉",this);

    imp->action_zoom_in = new QAction(QIcon("./image/zoom_in.png"),"放大",this);
    imp->action_zoom_out = new QAction(QIcon("./image/zoom_out.png"),"缩小",this);

    imp->menu_file->addActions({ imp->action_file_new,imp->action_file_open,
                               imp->action_file_save,  imp->action_file_other_save,
                                imp->action_print});
    imp->menu_window->addAction(imp->action_draw);
    imp->menu_edit->addActions({imp->action_zoom_in,imp->action_zoom_out});
}
canvas* sheetflow_main::create_canvas_body()
{
     canvas* canva = new canvas();
     qDebug() << "create_body";
     imp->mdiare->addSubWindow(canva);
     return canva;

}

void sheetflow_main::set_mdiare()
{
    imp->mdiare->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    imp->mdiare->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(imp->mdiare);
    imp->mdiare->setViewMode (QMdiArea::TabbedView);

}



void sheetflow_main::create_toolbars()
{
    imp->toolbar_file = addToolBar("文件");
    imp->toolbar_window = addToolBar("窗口");
    imp->toolbar_edit = addToolBar("编辑");

    imp->toolbar_file->addActions({ imp->action_file_new,imp->action_file_open,
                                    imp->action_file_save,  imp->action_file_other_save,
                                     imp->action_print});
    imp->toolbar_window->addAction(imp->action_draw);
    imp->toolbar_edit->addActions({imp->action_zoom_in,imp->action_zoom_out});

}
