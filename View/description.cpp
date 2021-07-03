#include "description.h"

Description::Description(QWidget *parent) : QLabel(parent)
{
    setWordWrap(true);
    setMouseTracking(true);
    setMinimumSize(730, 120);
    setText("Menu");

    /*
    m_lndm_menu = new QMenu(this);
    connect(this, SIGNAL(linkActivated(const QString &)), this, SLOT(lndmNameLinkClicked(const QString &)));
    connect(m_lndm_menu, SIGNAL(triggered(QAction*)), SLOT(lndmMenuDoAction(QAction*)));
    */
}

void Description::lndmMenuDoAction(QAction *qa)
{
    qDebug() << "blabla " << qa->text();
}

void Description::lndmNameLinkClicked(const QString &ttt)
{
    qDebug() << ttt;
    m_lndm_menu->clear();
    m_lndm_menu->addAction("&wow - it is " + ttt);
    m_lndm_menu->addAction("&dfgdf - it is " + ttt);
    m_lndm_menu->addAction("&fuckckck - it is " + ttt);
    m_lndm_menu->popup(QCursor::pos());
}
