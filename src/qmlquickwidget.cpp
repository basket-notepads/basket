#include "qmlquickwidget.h"
#include <QScrollArea>


void BnpQuickWidget::dragMoveEvent(QDragMoveEvent* e)
{
    QQuickWidget::dragMoveEvent(e);
    m_parentScrollArea->ensureVisible(e->pos().x(), e->pos().y());
}

