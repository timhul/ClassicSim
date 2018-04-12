import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    height: parent.height
    width: parent.width

    color: root.darkDarkGray

    RectangleBorders {
        height: parent.height
        width: 850
        anchors {
            right: parent.right
        }

        color: root.darkGray

        RectangleBorders {
            id: sortRect
            height: parent.height * 0.05
            width: parent.width
        }

        ScrollView {
            width: parent.width

            anchors {
                top: sortRect.bottom
                right: parent.right
                bottom: parent.bottom
            }

            ListView {
                model: weaponModel
                boundsBehavior: Flickable.StopAtBounds

                clip: true

                delegate: ItemEntryWeapon {
                    entryName: name
                    entrySpeed: speed
                    entryDps: dps
                    entryPatch: patch
                    entrySource: source
                    entryType: type
                    entryReq: req_lvl
                    entryItemlvl: item_lvl
                    entryQuality: quality
                    entryIcon: icon
                }
            }
        }
    }
}
