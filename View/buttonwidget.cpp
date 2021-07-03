#include "buttonwidget.h"
#include <QPushButton>

Buttonwidget::Buttonwidget(QWidget *parent) : QVBoxLayout(parent)
{
    setSpacing(10);
    addStretch(1);
    setAlignment(Qt::AlignTop);
}

void Buttonwidget::addActionButton(UserAction *action)
{
    button_list.push_back(new QPushButton(action->buttonName));
    button_list.last()->setMinimumSize(220, 70);
    button_list.last()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    addWidget(button_list.last());
    connect(button_list.last(), SIGNAL(clicked()), action, SLOT(slotAction()));
    if (action->buttonName == "Создать мир"){
        button_list.last()->setText(action->buttonName + " [W]");
        keyW = new QShortcut(button_list.last());
        keyW->setKey(Qt::Key_W);
        connect(keyW, SIGNAL(activated()), action, SLOT(slotAction()));
    }
    if (action->buttonName == "Прогуляться"){
        button_list.last()->setText(action->buttonName + " [Q]");
        keyQ = new QShortcut(button_list.last());
        keyQ->setKey(Qt::Key_Q);
        connect(keyQ, SIGNAL(activated()), action, SLOT(slotAction()));
    }
    if (action->buttonName == "Назад"){
        button_list.last()->setText(action->buttonName + " [R]");
        keyR = new QShortcut(button_list.last());
        keyR->setKey(Qt::Key_R);
        connect(keyR, SIGNAL(activated()), action, SLOT(slotAction()));
        if(action->isOnMap) {
            button_list.last()->setText(action->buttonName + " [SPACE]/[R]");
            keySpace = new QShortcut(button_list.last());
            keySpace->setKey(Qt::Key_Space);
            connect(keySpace, SIGNAL(activated()), action, SLOT(slotAction()));
        }
    }
    if (action->buttonName.contains("Исследовать мир ")){
        button_list.last()->setText(action->buttonName + " [E]");
        keyE = new QShortcut(button_list.last());
        keyE->setKey(Qt::Key_E);
        connect(keyE, SIGNAL(activated()), action, SLOT(slotAction()));
    }
    if (action->buttonName == "Запомнить место"){
        button_list.last()->setText(action->buttonName + " [SPACE]");
        keySpace = new QShortcut(button_list.last());
        keySpace->setKey(Qt::Key_Space);
        connect(keySpace, SIGNAL(activated()), action, SLOT(slotAction()));
    }
    if ((action->buttonName == "Собрать цветочки") ||
        (action->buttonName == "Добыть руду") ||
        (action->buttonName == "Срубить") ||
        (action->buttonName == "Нарвать травы") ||
        (action->buttonName == "Подобрать")
            ) {
        button_list.last()->setText(action->buttonName + " [1]");
        keySpace1 = new QShortcut(button_list.last());
        keySpace1->setKey(Qt::Key_1);
        connect(keySpace1, SIGNAL(activated()), action, SLOT(slotAction()));
    }
    if (action->buttonName == "На уровень глубже"){
        button_list.last()->setText(action->buttonName + " [N]");
        keyN = new QShortcut(button_list.last());
        keyN->setKey(Qt::Key_N);
        connect(keyN, SIGNAL(activated()), action, SLOT(slotAction()));
    }
    if ((action->buttonName == "На уровень ближе к генератору") ||
        (action->buttonName == "Вернуться к генератору")){
        button_list.last()->setText(action->buttonName + " [B]");
        keyB = new QShortcut(button_list.last());
        keyB->setKey(Qt::Key_B);
        connect(keyB, SIGNAL(activated()), action, SLOT(slotAction()));
    }
}

void Buttonwidget::removeAll()
{
    while(button_list.size() > 0){
        disconnect(button_list.last());
        delete button_list.last();
        removeWidget(button_list.last());
        button_list.pop_back();
    }
}
