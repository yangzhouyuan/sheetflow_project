#include "attribute.h"
#include <QGridLayout>///采用表格布局
#include <iterator>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>


std::unique_ptr<attribute> attribute::make(QMap<QString, QString> data, QWidget *parent)
{
    auto attribute_object = std::unique_ptr<attribute>(new attribute(std::move(data),parent));
    if(!attribute_object->init ())
    {
        qDebug() << "11";
        return nullptr ;
    }
    else
    {
        qDebug() << "22";
        return attribute_object;
    }
}
attribute::attribute(QWidget *parent)
    : QWidget(parent)
{


}
attribute::attribute(QMap<QString, QString> data, QWidget *parent)
    :QWidget(parent),item_data_(std::move(data))
{
}

bool attribute::init()
{

    auto layout = new QGridLayout(this);

    QMap<QString, QString>::const_iterator iter;
    for (iter = item_data_.cbegin(); iter != item_data_.cend(); iter++)
    {
        layout->addWidget(new QLabel(iter.key(),this));
        layout->addWidget(new QLineEdit(iter.value(), this));

    }

    auto button_submit = std::make_unique<QPushButton>("提交",this);
    layout->addWidget(button_submit.release());

    return true;
}
