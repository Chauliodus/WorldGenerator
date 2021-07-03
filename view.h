#ifndef VIEW_H
#define VIEW_H

#include "game.h"
#include <QDebug>
#include <QWidget>
#include <QLayoutItem>
#include <QPushButton>
#include <View/buttonwidget.h>
#include <View/description.h>
#include <View/gamefield.h>
#include <View/statepanel.h>
#include "useraction.h"
#include "View/pixmapitem.h"
#include <QShortcut>

/* Класс главного окна. Содержит игровое поле, окно словесного описания, шкалу состояния (отображает
 * состояние главного героя, кнопки "инвентарь", "навыки" и пр.) и панель с кнопками действий, таких как
"содать мир", "исследовать мир", "идти глубже в мир" и т.п.*/

class View : public QWidget
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr, Game * game = nullptr);
    ~View(){}
    Game * game;
    Buttonwidget * buttonwidget;
    Description * description;
    Gamefield * gamefield;
    Statepanel * statepanel;
    QVBoxLayout * vbox; // содержит окно описаний, игровое поле и шкалу состояния
    QHBoxLayout * hbox; // содержит вертикальный лэйаут и лэйаут с кнопками действий
    QWidget inventory;
    QGraphicsView inv_view;
    QGraphicsScene inv_scene;
    QVector<PixmapItem *> inventory_item;
    QVector<UserAction *> action_list;
    QVector<PixmapItem *> lndm_label_list;
    QShortcut *keyI; // inventory - ready
    QShortcut *keyH; // hero (planed)
    QShortcut *keyU; // world (planed)
    void drawLandmPrevs();
signals:

public slots:
    void drawWorld();
    void drawLevel();
    void drawLandmark(Landmark *);
    void redrawLandmark();
    void showInventory();
    void showMessageInDescriptionField(QString);
};

#endif // VIEW_H
