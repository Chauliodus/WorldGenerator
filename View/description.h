#ifndef DESCRIPTION_H
#define DESCRIPTION_H

#include <QContextMenuEvent>
#include <QDebug>
#include <QLabel>
#include <QMenu>
#include <QWidget>

class Description : public QLabel
{
    Q_OBJECT
public:
    explicit Description(QWidget *parent = nullptr);
    void printMessage(const QString &);
protected:
    virtual void contextMenuEvent(QContextMenuEvent * pe) { m_lndm_menu->exec(pe->globalPos()); }
public slots:
    void lndmMenuDoAction(QAction * qa);
    void lndmNameLinkClicked(const QString &ttt);
private:
    QMenu * m_lndm_menu;

signals:
    friend void QLabel::linkActivated(const QString &link);
public slots:

};

#endif // DESCRIPTION_H
