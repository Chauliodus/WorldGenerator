#include "statescene.h"

Statescene::Statescene()
{
    QPixmap pict("../res/statepanel/statepanel.png");
    addPixmap(pict);

    characteristics.statebutton = StateButtons::CHAR;
    characteristics.setX(10);
    characteristics.setY(10);
    characteristics.type = PixmapItemTypes::STATE_PANEL_BUTTON;
    QPixmap p("../res/statepanel/characteristics.png");
    characteristics.setPixmap(p);
    characteristics.hovered = false;

    worldbutton.statebutton = StateButtons::WINFO;
    worldbutton.setX(10 + 55 + 10);
    worldbutton.setY(10);
    worldbutton.type = PixmapItemTypes::STATE_PANEL_BUTTON;
    QPixmap p2("../res/statepanel/worldinfo.png");
    worldbutton.setPixmap(p2);
    worldbutton.hovered = false;

    physics.setX(10 + 124 + 10 + 55 + 10);
    physics.setY(10);
    physics.type = PixmapItemTypes::STATE_PANEL_BUTTON;
    QPixmap p1("../res/statepanel/physics.png");
    physics.setPixmap(p1);
    physics.statebutton = StateButtons::PHYS;

    logic.setX(10 + 124 + 10 + 55 + 10);
    logic.setY(15 + 13);
    logic.type = PixmapItemTypes::STATE_PANEL_BUTTON;
    QPixmap p11("../res/statepanel/logic.png");
    logic.setPixmap(p11);
    logic.statebutton = StateButtons::LOG;

    ethics.setX(10 + 124 + 10 + 55 + 10);
    ethics.setY(30 + 13);
    ethics.type = PixmapItemTypes::STATE_PANEL_BUTTON;
    QPixmap p111("../res/statepanel/ethics.png");
    ethics.setPixmap(p111);
    ethics.statebutton = StateButtons::ETH;

    willpower.setX(10 + 124 + 10 + 55 + 10);
    willpower.setY(45 + 13);
    willpower.type = PixmapItemTypes::STATE_PANEL_BUTTON;
    QPixmap p1111("../res/statepanel/willpower.png");
    willpower.setPixmap(p1111);
    willpower.statebutton = StateButtons::WPOW;

    inventory.statebutton = StateButtons::INV;
    inventory.setX(10 + 10 + 124 + 10 + 394 + 55 + 10);
    inventory.setY(10);
    inventory.type = PixmapItemTypes::STATE_PANEL_BUTTON;
    QPixmap p22("../res/statepanel/inventory.png");
    inventory.setPixmap(p22);
    inventory.hovered = false;

    addItem(&characteristics);
    addItem(&worldbutton);
    addItem(&physics);
    addItem(&logic);
    addItem(&ethics);
    addItem(&willpower);
    addItem(&inventory);
}

void Statescene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
}
