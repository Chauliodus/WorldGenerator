#ifndef USERACTION_H
#define USERACTION_H

#include "game.h"
#include <functional>
#include <QObject>

class View;

/* Пользовательское действие - класс, который получается от вьюхи и передается виджету с кнопками.
Содержит строку с названием кнопки, строку с названием функции (вызывается через метаобъектную систему) и
указатель на объект, чью функцию нужно вызвать. */

class UserAction : public QObject
{
    Q_OBJECT
public:
    explicit UserAction(QString, QString, Game *);
    UserAction(QString, QString, View *);
    UserAction(QString, QString, Landmark *);
    ~UserAction(){}
    void initShortcuts();
    Game            * game;
    View            * view;
    Landmark        * landmark;
    QString         buttonName;
    QString         functionName;
    bool isOnMap;
    //std::function<void()> action;
private:

signals:

public slots:
    void slotAction();
};

#endif // USERACTION_H
