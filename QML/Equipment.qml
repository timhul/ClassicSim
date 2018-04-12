import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    height: parent.height
    width: parent.width

    color: root.darkDarkGray

    RectangleBorders {
        height: parent.height
        width: parent.width
        anchors {
            right: parent.right
        }

        color: root.darkGray

        ScrollView {
            height: parent.height * 0.9
            width: parent.width

            y: parent.height * 0.05


            ListView {
                model: weaponModel
                boundsBehavior: Flickable.StopAtBounds

                delegate: ItemEntryWeapon {
                    entryName: name
                    entryDps: dps
                    entrySpeed: speed
                    entryPatch: patch
                }
            }
        }
    }
}
