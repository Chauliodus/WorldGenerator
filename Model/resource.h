#ifndef RESOURCE_H
#define RESOURCE_H

#include <QObject>

class Resource : public QObject
{
    Q_OBJECT
public:
    explicit Resource(QObject *parent = nullptr);
    Resource(QString, QString, int); // ресурс собирается за 1 раз
    QString name;
    QString required_item;
    bool is_item_in_stack;
    int count;
signals:

public slots:
};

#endif // RESOURCE_H
