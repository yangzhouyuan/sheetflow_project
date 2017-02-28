#include "sheetflow_main.h"
#include "ui_sheetflow_main.h"

sheetflow_main::sheetflow_main(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sheetflow_main)
{
    ui->setupUi(this);
    create_toolbar();
}

sheetflow_main::~sheetflow_main()
{
    delete ui;
}

void sheetflow_main::create_toolbar()
{
    file_toolbar_->addActions({ui->file_new_action,ui->file_open_action,
                              ui->file_save_action,ui->fiel_other_action,
                              ui->printf_action});
    window_toolbar_->addAction(ui->display_draw_action);
    edit_toolbar_->addActions({ui->zoom_in_action, ui->zoom_out_action});
}
