#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <QWidget>
#include <memory>
#include <utility>
#include <QMap>
#include <attribute.h>
#include <QGridLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QPushButton>

class attribute : public QWidget
{
    Q_OBJECT
public:
    static std::unique_ptr<attribute> make (QMap<QString, QString> data,QWidget *parent = nullptr);
    explicit attribute(QWidget *parent = 0);
    explicit attribute (QMap<QString,QString> data, QWidget* parent);
     QMap<QString, QString> apply ()  { return chang_value; }
     void sender_button_signal ();
private:
    bool init ();
signals:
    void commit ();

public slots:

private:
     QMap<QString, QString>item_data_;
     QMap<QString, QString> chang_value;
     QPushButton* button_commit_ = nullptr;
};

#endif // ATTRIBUTE_H
