import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    id: eqRect
    height: parent.height
    width: parent.width

    color: root.darkDarkGray

    state: "MAINHAND"

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

                EquipmentSlotBox {
                    id: helmSlot

                    state: eqRect.state
                    slotString: "HELM"

                    onSelectItem: eqRect.state = "HELM"
                }

                EquipmentSlotBox {
                    id: neckSlot

                    onSelectItem: eqRect.state = "NECK"
                }

                EquipmentSlotBox {
                    id: shoulderSlot

                    onSelectItem: eqRect.state = "SHOULDERS"
                }

                EquipmentSlotBox {
                    id: backSlot

                    onSelectItem: eqRect.state = "BACK"
                }

                EquipmentSlotBox {
                    id: chestSlot

                    onSelectItem: eqRect.state = "CHEST"
                }

                EquipmentSlotBox {
                    id: shirtSlot
                }

                EquipmentSlotBox {
                    id: tabardSlot
                }

                EquipmentSlotBox {
                    id: wristSlot

                    onSelectItem: eqRect.state = "WRIST"
                }
            }

            Row {
                height: 46
                width: 46*3 + 12

                x: 138
                y: 395

                spacing: 6

                EquipmentSlotBox {
                    id: mainhandSlot

                    state: eqRect.state
                    slotString: "MAINHAND"
                    iconSource: equipment.mainhandIcon

                    onSelectItem: eqRect.state = "MAINHAND"
                }

                EquipmentSlotBox {
                    id: offhandSlot

                    state: eqRect.state
                    slotString: "OFFHAND"
                    iconSource: equipment.offhandIcon

                    onSelectItem: eqRect.state = "OFFHAND"
                }

                EquipmentSlotBox {
                    id: rangedSlot

                    onSelectItem: eqRect.state = "RANGED"
                }
            }

            EquipmentSlotBox {
                id: ammoSlot
                height: 34
                width: 34

                x: 307
                y: 400

                onSelectItem: console.log("Selecting ammo")
            }

            Column {
                width: 46
                height: parent.height

                x: 367
                y: 7

                spacing: 5

                EquipmentSlotBox {
                    id: gloveSlot

                    onSelectItem: console.log("Selecting gloves")
                }

                EquipmentSlotBox {
                    id: beltSlot

                    onSelectItem: console.log("Selecting belt")
                }

                EquipmentSlotBox {
                    id: legSlot

                    onSelectItem: console.log("Selecting legs")
                }

                EquipmentSlotBox {
                    id: bootSlot

                    onSelectItem: console.log("Selecting boots")
                }

                EquipmentSlotBox {
                    id: ring1Slot

                    onSelectItem: console.log("Selecting ring1")
                }

                EquipmentSlotBox {
                    id: ring2Slot

                    onSelectItem: console.log("Selecting ring2")
                }

                EquipmentSlotBox {
                    id: trinket1Slot

                    onSelectItem: console.log("Selecting trinket1")
                }

                EquipmentSlotBox {
                    id: trinket2Slot

                    onSelectItem: console.log("Selecting trinket2")
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

            visible: eqRect.state === "MAINHAND"

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

                    onEntryClicked: equipment.setSlot(eqRect.state, entryName)
                }
            }
        }

        ScrollView {
            width: parent.width

            visible: eqRect.state !== "MAINHAND"

            anchors {
                top: sortRect.bottom
                right: parent.right
                bottom: parent.bottom
            }

            ListView {
                model: itemModel
                boundsBehavior: Flickable.StopAtBounds

                clip: true

                delegate: ItemEntryWeapon {
                    entryName: name
                    entrySpeed: "0"
                    entryDps: "0"
                    entryPatch: patch
                    entrySource: source
                    entryType: type
                    entryReq: req_lvl
                    entryItemlvl: item_lvl
                    entryQuality: quality
                    entryIcon: icon

                    onEntryClicked: equipment.setSlot(eqRect.state, entryName)
                }
            }
        }
    }
}
