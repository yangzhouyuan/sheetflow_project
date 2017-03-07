#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <QWidget>
#include <memory>
#include <utility>
#include <QMap>
#include <attribute.h>

class attribute : public QWidget
{
    Q_OBJECT
public:
    static std::unique_ptr<attribute> make (QMap<QString, QString> &data,QWidget *parent = nullptr);
    explicit attribute(QWidget *parent = 0);
    explicit attribute (QMap<QString,QString> &data, QWidget* parent);
private:
    bool init ();
signals:

public slots:
private:
    const QMap<QString, QString>data_;
};

#endif // ATTRIBUTE_H
