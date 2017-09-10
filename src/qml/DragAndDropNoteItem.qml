import QtQuick 2.2
//import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0
import QtQml.Models 2.2

import org.kde.basket 1.0

Rectangle {
    id: item
    property string display
    property int explicitWidth: undefined
    border.color: DelegateModel.inSelected ? 'red' : 'yellow'

    implicitHeight: textNoteText.height + 8//margin
    implicitWidth: textNoteText.width + 8
    width: explicitWidth//listViewCol.width

    //Moving to NotesFilterModel
    /*x: model.display.X
    y: model.display.Y
    height: 30
    Component.onCompleted: {
        console.log('DragAndDropNoteItem onCompleted', model.index, x, y)
    }*/

    property Item aContentItem: listViewT.contentItem //Scroll-2

    Text {
        id: textNoteText
        text: item.display
        color: 'darkred'
        wrapMode: Text.WordWrap
    }

    MouseArea {
        id: mouseArea //areaDrag
        anchors.fill: parent
        drag.target: itemDraggable
        cursorShape: drag.active ? Qt.DragMoveCursor : Qt.IBeamCursor

        //TODO: remove demo code
        onClicked: {
            item.DelegateModel.inSelected = !item.DelegateModel.inSelected
            listViewCol.currentIndex = modelIndex
        }
    }
    Item {
        //Dummy item for integration with QML. QDrag is used for real dragging
        id: itemDraggable
        anchors.fill: parent
        Drag.active: mouseArea.drag.active
        Drag.dragType: Drag.None
    }

    LinearGradient {
        id: topPlaceholder //inserter
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }
        height: 2

        start: Qt.point(0, 0)
        end: Qt.point(parent.width, 0)
        gradient: Gradient {
            GradientStop { position: 0; color: 'lightgreen' }
            GradientStop { position: 1; color: 'red' }
        }
        cached: true
        visible: false
    }
    LinearGradient {
        id: bottomPlaceholder
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        height: 2

        start: Qt.point(0, 0)
        end: Qt.point(parent.width, 0)
        gradient: Gradient {
            GradientStop { position: 0; color: 'orange' }
            GradientStop { position: 1; color: 'green' }
        }
        cached: true
        visible: false
    }

    IndividualDropArea {
        id: dropAreaAboveItem
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.verticalCenter
        }
    }
    Loader {
        id: loaderDropAreaBelowLastItem
        active: model.index == cModel.rowCount() - 1
        anchors {
            left: parent.left
            right: parent.right
            top: parent.verticalCenter
        }
        height: listViewCol.contentHeight - y
        sourceComponent: Component {
            IndividualDropArea {
                id: dropAreaBelowLastItem
                height: listViewCol.contentHeight - y
                dropIndex: model.index + 1
            }

        }
    }

    states: [
        State {
            name: "dragging"
            when: mouseArea.drag.active

            StateChangeScript {
                name: 'scriptDragStart'
                script:
                {
                    var serializedNote = JSON.stringify(cModel.get(modelIndex))
                    //TODO: use x-basket-note (drag out -> rich text, not json)

                    //Render feedback pixmap and initiate drag
                    item.grabToImage(function(grabResult) {
                        //callback
                        console.time("scriptDragStart");
                        var dropAction = cNoteDrag.dragObject(item, /*item.display*/serializedNote, grabResult);
                        if (dropAction == Qt.MoveAction) {
                            console.debug('scriptDragStart: myModel.remove')
                            cModel.deleteNote(model.index)
                        }
                        console.timeEnd("scriptDragStart");
                    });
                }
            }
        },
        State {
            name: 'droppingAbove'
            when: dropAreaAboveItem.containsDrag
            PropertyChanges {
                target: topPlaceholder
                visible: true
            }
        },
        State {
            name: 'droppingBelow'
            when: loaderDropAreaBelowLastItem.item.containsDrag
            PropertyChanges {
                target: bottomPlaceholder
                visible: true
            }
        }
    ]
}
