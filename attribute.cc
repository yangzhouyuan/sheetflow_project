#include "attribute.h"
#include <QGridLayout>///采用表格布局
#include <iterator>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>



std::unique_ptr<attribute> attribute::make(QMap<QString, QString> data, QWidget *parent)
{
    auto attribute_object = std::make_unique<attribute>(new attribute(data, parent));

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
    :QWidget(parent),item_data_(data)
{

}

bool attribute::init()
{
    qDebug()<< "init";

    auto layout = new QGridLayout(this);
    qDebug() << item_data_.begin().key() + "...........";
    QMap<QString, QString>::const_iterator iter;
    for (iter = item_data_.cbegin(); iter != item_data_.cend(); iter++)
    {
        qDebug() << iter.key() + "5555" << ":::" << iter.value() + "5555";
        layout->addWidget(new QLabel(iter.key(),this));
        layout->addWidget(new QLineEdit(iter.value(), this));
    }

    qDebug() << "123";
    auto button_submit = std::make_unique<QPushButton>("提交",this);
    layout->addWidget(button_submit.release());

    return true;
}
