#ifndef MEETING_H
#define MEETING_H

#include <QObject>

class Game;
class Hero;
class Unit;

class Meeting : public QObject
{
    Q_OBJECT
public:
    explicit Meeting(Hero *, Unit *, Game *parent = nullptr);
    Game * game;
    Hero * hero;
    QVector<Unit *> units;
signals:

public slots:
};

#endif // MEETING_H
