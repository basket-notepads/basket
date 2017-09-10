import QtQuick 2.6
import QtQuick.Controls 2.2 //1.4 //Scroll-2 - Controls vs. Controls 2
import QtQuick.Layouts 1.1

Item {
    /*ListModel {
        id: myModel
        ListElement {
            noteText: "1 The Phantom Menace"
        }
        ListElement {
            noteText: "2 Attack of the Clones"
        }
        ListElement {
            noteText: "3 Revenge of the Siths"
        }
        ListElement {
            noteText: "4 A New Hope"
        }
        ListElement {
            noteText: "5 The Empire Strikes Back"
        }
        ListElement {
            noteText: "6 Return of the Jedi"
        }
        ListElement {
            noteText: "7 The Force Awakens"
        }
        ListElement { noteText: '11 aa' }
        ListElement { noteText: '12 bb' }
        ListElement { noteText: '13 cc' }
        ListElement { noteText: '14 dd' }
        ListElement { noteText: '15 ee' }
        ListElement { noteText: '16 ff' }
        ListElement { noteText: '17 gg' }
        ListElement { noteText: '18 hh' }
        ListElement { noteText: '19 ii' }
        ListElement { noteText: '20 gg' }
        ListElement { noteText: '21 kk' }
        ListElement { noteText: '22 ll' }
        ListElement { noteText: '23 mm' }
        ListElement { noteText: '24 nn' }
        ListElement { noteText: '25 oo' }
        ListElement { noteText: '26 pp' }
    }*/

    id: root
    width: 320
    height: childrenRect.height

        Rectangle {
            id: rectBasketBackground
            anchors.fill: parent
            color: cBasket.backgroundColor()
        }

        //ListViewTock {
        ListViewTick {
            width: 200
            height: childrenRect.height //TODO: test max opengl size - need a limit?
            id: listViewT
        }
}
