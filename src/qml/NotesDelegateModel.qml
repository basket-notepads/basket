import QtQuick 2.0
import QtQml.Models 2.2

import org.kde.basket 1.0

DelegateModel {
    //id: delegateModel_cModel
    model: cModel
    delegate: DragAndDropNoteItem {
        property int modelIndex: index //for access from outside

        id: delegateItem
        display: model.display.Name //model.noteText
        explicitWidth: listViewCol.width //if not set, implicitWidth will be used
        //height: 30 //Moving to

        //use model.dropMimeData
    }
    groups: [
        DelegateModelGroup { name: 'selected' }
    ]
}
