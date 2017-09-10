#include "qmlbasket.h"
#include <QDebug>
#include <QCursor>

Basket::Basket(QObject *parent) :
    QObject(parent)
{
    tagsMenu = new QMenu();
    tagsMenu->addAction("Tag1");
    tagsMenu->addAction("Tag2");
    tagsMenu->addAction("Tag3");
    tagsMenu->addAction("Tag4");
}

Basket::~Basket()
{
    tagsMenu->deleteLater();
}

void Basket::popupTagsMenu(int x, int y)
{
    //tagsMenu->popup(QPoint(x, y));
    tagsMenu->popup(QCursor::pos());
}
