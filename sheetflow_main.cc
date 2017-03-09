#include "sheetflow_main.h"
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
#include <QDockWidget>
#include "canvas_body.h"
#include <attribute.h>
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
    std::unique_ptr<QDockWidget> drawer_ = std::make_unique<QDockWidget>();
    std::unique_ptr<drag_widget> draw_widget;

    std::unique_ptr<QDockWidget> attribute_ = std::make_unique<QDockWidget>();
    std::unique_ptr<attribute> attribute_content_;

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
    set_draw_widget_name();
    set_draw();
    set_attribute();
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
    auto canva = create_canvas_body();

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

canvas_view* sheetflow_main::create_canvas_body()
{
     auto canva = canvas_view::make ();
     auto ptr_canva = canva.get();

     connect(ptr_canva, &canvas_view::selete_change, this, &sheetflow_main::notify_attribute);

     imp->mdiare->addSubWindow(canva.release ());
     return ptr_canva;
}

void sheetflow_main::notify_attribute(bool ok)
{
    imp->attribute_->setWidget(nullptr);
    if(!ok)
    {
        return;
    }
    auto activite_canvas = actvite_body();///是否有活动窗口
    if(activite_canvas == nullptr)
    {
        return;
    }
    auto attribute_map = activite_canvas->selete_item_data();///返回活动窗口里面item的属性

    if(attribute_map.size() == 0)
    {
        return;
    }
   imp->attribute_content_ = attribute::make(std::move(attribute_map),this);//把获取到的数据传到属性类去创建widget
   set_attribute_window();
}


canvas_view *sheetflow_main::actvite_body()
{
    if(QMdiSubWindow *active_subwindow = imp->mdiare->activeSubWindow())
    {
        canvas_view* canvas_ptr = dynamic_cast<canvas_view*>(active_subwindow->widget());
        //assert (canvas_ptr);
        return canvas_ptr;
    }
    else
    {
        return nullptr;
    }

}

void sheetflow_main::set_attribute()
{
    imp->attribute_->setMaximumWidth(250);
    imp->attribute_->setMinimumWidth(250);
    imp->attribute_->setAllowedAreas (Qt::RightDockWidgetArea);
    addDockWidget (Qt::RightDockWidgetArea, imp->attribute_.get ());


}

void sheetflow_main::set_attribute_window()
{
     imp->attribute_->setWidget (imp->attribute_content_.get());
     if (imp->attribute_->isHidden())
     {
         imp->attribute_->show();
     }
     else
     {
         imp->attribute_->isHidden();
     }


}

void sheetflow_main::set_draw()
{
    imp->drawer_->setMaximumWidth (150);
    imp->drawer_->setMinimumWidth (150);

    imp->draw_widget->setMaximumWidth (140);
    imp->draw_widget->setMinimumWidth (140);

    imp->drawer_->setWidget (imp->draw_widget.get ());

    connect (imp->draw_widget.get(), &drag_widget::button_triggered, [] (const QString& text) { qDebug () << text; });

    imp->drawer_->setAllowedAreas (Qt::LeftDockWidgetArea);
    addDockWidget (Qt::LeftDockWidgetArea, imp->drawer_.get ());
}

void sheetflow_main::set_mdiare()
{
    imp->mdiare->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    imp->mdiare->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(imp->mdiare);
    imp->mdiare->setViewMode (QMdiArea::TabbedView);

}

void sheetflow_main::set_draw_widget_name()
{
    std::vector<QString>  labels = {"加工", "检验", "产成品"};
    std::vector<QString> buttons = {"原材料", "连线1", "连线2"};
     imp->draw_widget =drag_widget::make(labels, buttons);

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
