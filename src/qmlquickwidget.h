#ifndef QMLQUICKWIDGET_H
#define QMLQUICKWIDGET_H

#include <QtQuickWidgets/QQuickWidget>

class QScrollArea;

class BnpQuickWidget : public QQuickWidget
{
public:
    BnpQuickWidget(QWidget* parent) : QQuickWidget(parent) {}

    QScrollArea* m_parentScrollArea;
protected:
    void dragMoveEvent(QDragMoveEvent* e) override;
};

#endif // QMLQUICKWIDGET_H
