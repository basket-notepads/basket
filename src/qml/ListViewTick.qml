import QtQuick 2.0
import QtQuick.Layouts 1.1


ListView {
    id: listViewCol
    focus: true
    anchors.margins: 8
    model: NotesDelegateModel {
        id: delegateModel_cModel
    }
    displaced: Transition {
        NumberAnimation { properties: "x,y" }
    }

}
