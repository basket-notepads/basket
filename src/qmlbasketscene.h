/*
 *   Copyright (C) 2017 by Gleb Baryshev
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef QMLBASKETSCENE_H
#define QMLBASKETSCENE_H

#include <QtQuickWidgets/QQuickWidget>
#include <QScrollArea>
#include <functional>
#include "notedrag.h"
#include "qmlquickwidget.h"

class Note;

class Utils;
class Basket;
namespace qmlbnp {
    class NoteProperties;
    class NotesModel;
    class NotesFilterModel;
}

/* [FIXME]
  QQuickWidget stacked and not reloaded (see QStackedWidget *m_stack)
  Memory consumption - ?
 */
class QmlBasketScene : public QObject
{
    Q_OBJECT
public:
    QmlBasketScene(QWidget* parent);

    QScrollArea* scrollArea() { return &m_scrollArea; }
    BnpQuickWidget* quickWidget() { return &m_quickWidget; }

    std::function<Note*()> GetFirstNote;
private:
    void addSampleDataToModel();

    QScrollArea m_scrollArea;
    BnpQuickWidget m_quickWidget;

    QmlNoteDrag* cNoteDrag;
    Utils* cUtils;
    Basket* cBasket;
    qmlbnp::NoteProperties* cNoteProperties;
    qmlbnp::NotesModel* cModel;
};

#endif // QMLBASKETSCENE_H
