#ifndef IDEOLOGY_H
#define IDEOLOGY_H

#include <QObject>

class Ideology : public QObject
{
    Q_OBJECT
public:
    explicit Ideology(QObject *parent = nullptr);
    QString name;
signals:

public slots:
};

#endif // IDEOLOGY_H
