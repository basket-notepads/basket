#ifndef BASKET_H
#define BASKET_H

#include <QObject>
#include <QColor>
#include <QMenu>

class Basket : public QObject
{
    Q_OBJECT
private:
    QMenu* tagsMenu;
public:
    explicit Basket(QObject *parent = 0);
    ~Basket();

    Q_INVOKABLE QColor backgroundColor() { return QColor("#e6ffcc"); }
    Q_INVOKABLE void popupTagsMenu(int x, int y);

signals:

public slots:


};

#endif // BASKET_H
