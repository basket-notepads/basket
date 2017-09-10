import QtQuick 2.0

DropArea {
    id: dropArea
    //property bool isLast: model.index === listViewCol.count - 1
    height: parent.height
    keys: ["text/plain"] //TODO: notes, images

    property int dropIndex: model.index  //On drop insert at index

    onDropped: {
        //if (drop.hasText)
        if (drop.proposedAction == Qt.MoveAction || drop.proposedAction == Qt.CopyAction) {
            //drop: DragEvent
            var obj
            try {
                obj = JSON.parse(drop.text)
            }
            catch (SyntaxError) {
                //not in json format
                obj = Object()
                obj.Name = drop.text
                obj.X = 13; obj.Y = 13
            }

            console.debug('dropArea.onDropped', drop.text)
            cModel.insertNote(dropArea.dropIndex, obj.Name, obj.X, obj.Y)
            //insert C++:
            //Using C++ Models with Qt Quick Views
            //use model.dropMimeData (qthelp://model-view-programming.html)
            drop.acceptProposedAction()
        }
    }
}
