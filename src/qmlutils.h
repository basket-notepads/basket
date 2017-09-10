#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QColor>
#include <QJSValue>

class Utils : public QObject
{
    Q_OBJECT
public:
    Utils();
    Q_INVOKABLE QColor highlightColor();
    Q_INVOKABLE QColor lighter(QColor color, int factor = 150);
    Q_INVOKABLE QColor darker(QColor color, int factor = 200);
    Q_INVOKABLE void Inspect(QJSValue ctx);
};

#endif // UTILS_H
