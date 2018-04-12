import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    height: parent.height
    width: parent.width

    color: root.darkDarkGray

    RectangleBorders {
        width: parent.width - 850
        height: parent.height

        rectColor: root.darkDarkGray

        Image {
            x: parent.width / 2 - width / 2
            y: 30
            source: "Assets/char_slots.png"

            height: 448
            width: 426

            Column {
                width: 46
                height: parent.height

                x: 12
                y: 7

                spacing: 5

                Rectangle {
                    id: helmSlot
                    height: 46
                    width: 46

                    radius: 5
                    color: "transparent"
                    border.color: "white"
                    border.width: 1
                }

                Rectangle {
                    id: neckSlot
                    height: 46
                    width: 46

                    radius: 5
                    color: "transparent"
                    border.color: "white"
                    border.width: 1
                }

                Rectangle {
                    id: shoulderSlot
                    height: 46
                    width: 46

                    radius: 5
                    color: "transparent"
                    border.color: "white"
                    border.width: 1
                }

                Rectangle {
                    id: backSlot
                    height: 46
                    width: 46

                    radius: 5
                    color: "transparent"
                    border.color: "white"
                    border.width: 1
                }

                Rectangle {
                    id: chestSlot
                    height: 46
                    width: 46

                    radius: 5
                    color: "transparent"
                    border.color: "white"
                    border.width: 1
                }

                Rectangle {
                    id: shirtSlot
                    height: 46
                    width: 46

                    radius: 5
                    color: "transparent"
                    border.color: "white"
                    border.width: 1
                }

                Rectangle {
                    id: tabardSlot
                    height: 46
                    width: 46

                    radius: 5
                    color: "transparent"
                    border.color: "white"
                    border.width: 1
                }

                Rectangle {
                    id: wristSlot
                    height: 46
                    width: 46

                    radius: 5
                    color: "transparent"
                    border.color: "white"
                    border.width: 1
                }
            }

            Row {
                height: 46
                width: 46*3 + 10

                x: 138
                y: 395

                spacing: 6

                Rectangle {
                    id: mainhandSlot
                    height: 46
                    width: 46

                    radius: 5
                    color: "transparent"
                    border.color: "white"
                    border.width: 1
                }

                Rectangle {
                    id: offhandSlot
                    height: 46
                    width: 46

                    radius: 5
                    color: "transparent"
                    border.color: "white"
                    border.width: 1
                }

                Rectangle {
                    id: rangedSlot
                    height: 46
                    width: 46

                    radius: 5
                    color: "transparent"
                    border.color: "white"
                    border.width: 1
                }
            }

            Rectangle {
                id: ammoSlot
                height: 34
                width: 34

                x: 307
                y: 400

                radius: 5
                color: "transparent"
                border.color: "white"
                border.width: 1
            }

            Column {
                width: 46
                height: parent.height

                x: 367
                y: 7

                spacing: 5

                Rectangle {
                    id: gloveSlot
                    height: 46
                    width: 46

                    radius: 5
                    color: "transparent"
                    border.color: "white"
                    border.width: 1
                }

                Rectangle {
                    id: beltSlot
                    height: 46
                    width: 46

                    radius: 5
                    color: "transparent"
                    border.color: "white"
                    border.width: 1
                }

                Rectangle {
                    id: legSlot
                    height: 46
                    width: 46

                    radius: 5
                    color: "transparent"
                    border.color: "white"
                    border.width: 1
                }

                Rectangle {
                    id: bootSlot
                    height: 46
                    width: 46

                    radius: 5
                    color: "transparent"
                    border.color: "white"
                    border.width: 1
                }

                Rectangle {
                    id: ring1Slot
                    height: 46
                    width: 46

                    radius: 5
                    color: "transparent"
                    border.color: "white"
                    border.width: 1
                }

                Rectangle {
                    id: ring2Slot
                    height: 46
                    width: 46

                    radius: 5
                    color: "transparent"
                    border.color: "white"
                    border.width: 1
                }

                Rectangle {
                    id: trinket1Slot
                    height: 46
                    width: 46

                    radius: 5
                    color: "transparent"
                    border.color: "white"
                    border.width: 1
                }

                Rectangle {
                    id: trinket2Slot
                    height: 46
                    width: 46

                    radius: 5
                    color: "transparent"
                    border.color: "white"
                    border.width: 1
                }
            }


        }
    }

    RectangleBorders {
        height: parent.height
        width: 850
        anchors {
            right: parent.right
        }

        rectColor: root.darkDarkGray

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
