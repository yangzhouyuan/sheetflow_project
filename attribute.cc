#include "attribute.h"
#include <QGridLayout>///采用表格布局
#include <iterator>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>



std::unique_ptr<attribute> attribute::make(QMap<QString, QString> &data, QWidget *parent)
{
    auto attribute_object = std::make_unique<attribute>(new attribute(data, parent));
    if(!attribute_object->init ())
    {
        return attribute_object;
    }
    else
    {
        return nullptr;
    }
}
attribute::attribute(QWidget *parent)
    : QWidget(parent)
{

}
attribute::attribute(QMap<QString, QString> &data, QWidget *parent)
    :QWidget(parent),data_(data)
{
}

bool attribute::init()
{
    auto layout = new QGridLayout(this);
    QMap<QString, QString>::const_iterator iter ;

    for (iter = data_.cbegin(); iter != data_.cend(); ++iter)
    {

        layout->addWidget(new QLabel(iter.key(),this));
        layout->addWidget(new QLineEdit(iter.value(), this));
    }
    auto button_submit = std::make_unique<QPushButton>("提交",this);
    layout->addWidget(button_submit.release());
    return true;
}
