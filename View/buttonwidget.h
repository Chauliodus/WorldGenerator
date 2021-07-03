#ifndef BUTTONWIDGET_H
#define BUTTONWIDGET_H

#include <QBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QShortcut>
#include <useraction.h>

class Buttonwidget : public QVBoxLayout
{
    Q_OBJECT
public:
    explicit Buttonwidget(QWidget *parent = nullptr);
    QVector<QPushButton *> button_list;
    void addActionButton(UserAction *action);
    void removeAll();
    QShortcut       *keyW;
    QShortcut       *keyE;
    QShortcut       *keyQ;
    QShortcut       *keyR;
    QShortcut       *keySpace;
    QShortcut       *keySpace1;
    QShortcut       *keyN;
    QShortcut       *keyB;
signals:
public slots:
};

#endif // BUTTONWIDGET_H
