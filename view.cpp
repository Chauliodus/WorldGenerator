#include "view.h"
// Класс, управляющий всей графической составляющей программы. Вызывает методы для отрисовки уровней, персонажей, локаций и пр.,
// а так же кнопок
View::View(QWidget *parent, Game *game) : QWidget(parent), game(game)
{
    description = new Description();
    gamefield = new Gamefield();
    statepanel = new Statepanel();
    buttonwidget = new Buttonwidget();
    vbox = new QVBoxLayout();
    hbox = new QHBoxLayout(this);
    vbox->setSpacing(10);
    vbox->addStretch(1);
    vbox->setAlignment(Qt::AlignTop);
    vbox->addWidget(statepanel);
    vbox->addWidget(gamefield);
    vbox->addWidget(description);
    hbox->setSpacing(10);
    hbox->addStretch(1);
    hbox->setAlignment(Qt::AlignLeft);
    hbox->addLayout(buttonwidget);
    hbox->addLayout(vbox);

    setLayout(hbox);

    action_list.push_back(new UserAction("Создать мир", "createWorld", game));
    buttonwidget->addActionButton(action_list.last());

    connect(&statepanel->scene.inventory, &PixmapItem::sigOpenInventory, this, &View::showInventory);
    connect(game, &Game::sigWorldCreated, this, &View::drawWorld); // рисует только превьюшку свежесозданного мира, "вид из окна"
    connect(game, &Game::sigLevelChanged, this, &View::drawLevel); // когда герой переходит на др.ур.мира, отрисовывается новый ур.
    connect(game, &Game::sigWorldChanged, this, &View::drawLevel); // генератор миров рисуется в этой же функции, хотя является миром
    connect(game, &Game::sigLandmarkChanged, this, &View::drawLandmark); // вызывается при клике на значок ландмарки на карте уровня
    connect(game, &Game::sigLandmarkAddedOnMap, this, &View::redrawLandmark); // убирает кнопку "запомнить место" после запом.места
    connect(game, &Game::sigSendMessageToView, this, &View::showMessageInDescriptionField);
    keyI = new QShortcut(this);
    keyI->setKey(Qt::Key_I);
    connect(keyI, SIGNAL(activated()), this, SLOT(showInventory()));
}

void View::drawWorld() // Рисуется только "вид из окна"! Т.е. герой НЕ находится в этом мире. Curloc = generator
// Если пришли из мира, то рисуется генератор.
{
    buttonwidget->removeAll();
    gamefield->setPicture(game->new_world->picture);
    description->setText(game->new_world->description);
    UserAction * action = new UserAction("Исследовать мир " + game->new_world->name, "researchWorld", game);
    buttonwidget->addActionButton(action);
    UserAction * action2 = new UserAction("Создать мир", "createWorld", game);
    buttonwidget->addActionButton(action2);
}

void View::drawLevel() // данный метод рисует тот уровень, на котором находится герой, с минимальным набором кнопок.
// присутствуют миниатюры ландмарок - посещаемых объектов (интересных мест), которые либо видны издалека, либо посещены и помечены
// пользователем.
{
    gamefield->scene.clear();
    buttonwidget->removeAll();
    if (game->curloc->world->name == "Генератор миров") {
        gamefield->setPicture(game->generator->picture);
        description->setText(game->generator->description);
        UserAction * action = new UserAction("Исследовать мир " + game->new_world->name, "researchWorld", game);
        buttonwidget->addActionButton(action);
        UserAction * action2 = new UserAction("Создать мир", "createWorld", game);
        buttonwidget->addActionButton(action2);
        return;
    }
    QString level_desc = "Мир " + game->curloc->world->name + ", уровень: " + QString::number(game->curloc->level_num) + "\n";
    description->setText(level_desc + game->curloc->level->description);
    if (game->curloc->level_num < game->curloc->world->size - 1) {
        UserAction * action1 = new UserAction("На уровень глубже", "increaseLvl", game);
        buttonwidget->addActionButton(action1);
    }
    if (game->curloc->level_num > 0) {
        UserAction * action2 = new UserAction("На уровень ближе к генератору", "decreaseLvl", game);
        buttonwidget->addActionButton(action2);
    }
    if (game->curloc->level_num == 0) {
        UserAction * action3 = new UserAction("Вернуться к генератору", "decreaseLvl", game);
        buttonwidget->addActionButton(action3);
    }
    UserAction * action4 = new UserAction("Прогуляться", "researchLevel", game);
    buttonwidget->addActionButton(action4);

    gamefield->setPicture(game->curloc->level->picture);

    drawLandmPrevs();
}

void View::drawLandmark(Landmark * l)
// рисует крупную картинку с ландмаркой на фоне ландшафта, выводит описание ландмарки и кнопки управления ландмаркой
{
    if (l == nullptr) { drawLevel(); return; }
    game->curloc->lndm = l;
    game->curloc->landmark_num = l->number;
    gamefield->scene.isLndmShowing = true;
    l->onVisit();
    description->setText(l->description);
    gamefield->scene.clear();
    gamefield->setPicture(game->curloc->level->picture);
    gamefield->setPicture(l->picture);
    connect(&gamefield->scene, &Gamescene::sigLandmarkLeft, this, &View::drawLevel);
    buttonwidget->removeAll();
    // сделать ландмарку свой список действий, и на его основе передавать юзерэкшнам
    std::for_each(l->actions.begin(), l->actions.end(), [l, this](QPair<QString, QString>* pair){
        UserAction * userAction = new UserAction(pair->first, pair->second, l);
        buttonwidget->addActionButton(userAction);
    });
    UserAction * action1 = new UserAction("Назад", "drawLevel", this);
    buttonwidget->addActionButton(action1);
    if(l->isCanBeAddedOnMap == 1 && l->isAddedOnMap == 0 && l->isSeenFromAfar == 0) {
        UserAction * action4 = new UserAction("Запомнить место", "addOnMap", game);
        buttonwidget->addActionButton(action4);
    }
}

void View::redrawLandmark()
// Функция вызывается, когда ландмарка, до этого не посещенная игроком, добавляется на карту.
// При этом из списка кнопок удаляется кнопка "запомнить место", а ландмарка добавляется на карту.
{
    drawLevel();
    description->setText("Вы запоминаете место, чтобы вернуться к нему позднее.");
}

void View::showInventory()
{
    inventory.setGeometry(0,0,750,500);
    inv_view.setParent(&inventory);
    inv_view.setMouseTracking(true);
    inv_view.setScene(&inv_scene);
    inv_view.setMaximumSize(750,500);
    //QPixmap p("../res/back.png");
    //inv_scene.addPixmap(p);
    //inv_view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключим скроллбар по горизонтали
    int x = 5, y = 5, i = 0;
    qDebug() << game->hero->inventory.size();
    inventory_item.clear();
    if (game->hero->inventory.size() > 0){
        std::for_each(game->hero->inventory.begin(), game->hero->inventory.end(), [this, &x, &y, &i](Item * item){
            qDebug() << i << " " << item->name << "(" << item->count << ")"; i++;
            PixmapItem * pmi = new PixmapItem(item);
            //pmi->type = PixmapItemTypes::INVENTORY_ITEM;
            pmi->setX(x);
            pmi->setY(y);
            inv_scene.addItem(pmi);
            x += 75;
            if (x > 700) { y += 75; x = 5; }
            inventory_item.push_back(pmi);
            if (y > 75) inv_view.resize(750, y + 75); else inv_view.resize(x, 75);
        });
    }
    keyI = new QShortcut(&inventory);
    keyI->setKey(Qt::Key_I);
    connect(keyI, &QShortcut::activated, &inventory, &QWidget::close);
    inventory.show();
}

void View::showMessageInDescriptionField(QString message)
{
    description->setText(message);
}

void View::drawLandmPrevs() // для функции drawLevel() - рисует подсвечивающиеся pixmap item на каждый ландмарк текущего уровня
{
    gamefield->scene.landmark_item_list.clear();
    for (int i = 0; i < game->curloc->level->landmark_list.size(); i++){
        if (game->curloc->level->landmark_list[i]->isSeenFromAfar || game->curloc->level->landmark_list[i]->isAddedOnMap) {
            gamefield->scene.landmark_item_list.push_back(new PixmapItem(game->curloc->level->landmark_list[i]));
            gamefield->scene.landmark_item_list.last()->setX(game->curloc->level->landmark_list[i]->x);
            gamefield->scene.landmark_item_list.last()->setY(game->curloc->level->landmark_list[i]->y);
            gamefield->scene.addItem(gamefield->scene.landmark_item_list.last());
            QObject::connect(gamefield->scene.landmark_item_list.last(), &PixmapItem::sigLandmarkSelected, this, &View::drawLandmark);
        }
    }
}
