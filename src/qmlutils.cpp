#include "qmlutils.h"
#include <QGuiApplication>
#include <QPalette>
#include <QJSValueIterator>
#include <QDebug>


Utils::Utils()
{
}

QColor Utils::highlightColor()
{
    return QGuiApplication::palette().highlight().color();
}

QColor Utils::lighter(QColor color, int factor)
{
    return color.lighter(factor);
}

QColor Utils::darker(QColor color, int factor)
{
    return color.darker(factor);
}

void Utils::Inspect(QJSValue ctx)
{
    QString str = ctx.toString();
    qDebug(str.toLatin1());
    //const char* type = ctx.typeName();
    //qDebug((str + " - " + type).toLatin1());
    QJSValueIterator it(ctx);
    while (it.hasNext()) {
        it.next();
        qDebug() << it.name() << ": " << it.value().toString();
    }
}
