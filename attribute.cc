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

void attribute::sender_button_signal()
{
    qDebug() << "commit";
    emit commit();
}

bool attribute::init()
{

    auto layout = new QGridLayout(this);
    layout->setColumnMinimumWidth(1,30);
    QMap<QString, QString>::const_iterator iter;
    for (iter = item_data_.cbegin(); iter != item_data_.cend(); iter++)
    {
        layout->addWidget(new QLabel(iter.key(),this));
        layout->setVerticalSpacing(1);
        auto key = iter.key();
        auto edit = std::make_unique<QLineEdit> (iter.value(), this);
        connect(edit.get(), &QLineEdit::textChanged, [this, key = key] (auto&& text)
        {
            chang_value [key] = text;
        });

        layout->addWidget(edit.release ());
    }

    auto button_submit = std::make_unique<QPushButton>("提交",this);
    button_commit_ = button_submit.get();

    connect (button_submit.get (), &QPushButton::clicked, this, &attribute::sender_button_signal);

    layout->addWidget(button_submit.release());

    return true;
}
