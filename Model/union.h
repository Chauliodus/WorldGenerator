#ifndef UNION_H
#define UNION_H

#include <QObject>

class Union : public QObject
{
    Q_OBJECT
public:
    explicit Union(QObject *parent = nullptr);
    QString name;

signals:

public slots:
};

#endif // UNION_H
