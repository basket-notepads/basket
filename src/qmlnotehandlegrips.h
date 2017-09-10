#ifndef NOTEHANDLEGRIPS_H
#define NOTEHANDLEGRIPS_H

#include <QQuickPaintedItem>

class NoteHandleGrips : public QQuickPaintedItem
{
    Q_OBJECT
public:
    void paint(QPainter* painter) override;
};

class NoteInserter : public QQuickPaintedItem
{
    Q_OBJECT
public:
    void paint(QPainter* painter) override;
};

#endif // NOTEHANDLEGRIPS_H
