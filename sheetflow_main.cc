#include "sheetflow_main.h"
#include "ui_sheetflow_main.h"
#include <QToolBar>


struct impl_sheetflow_main
{

};

sheetflow_main::sheetflow_main(QWidget *parent) :
    QMainWindow(parent)
{
}

bool sheetflow_main::init()
{
    create_toolbars ();

    create_actions ();
    // create_buttons ();
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

void sheetflow_main::create_toolbars()
{
}

void sheetflow_main::connections()
{

}

void sheetflow_main::create_actions()
{

}
