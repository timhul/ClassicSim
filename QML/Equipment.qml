import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    id: eqRect
    height: parent.height
    width: parent.width

    color: root.darkDarkGray

    state: "MAINHAND"

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
            id: scrollWeapon
            width: parent.width

            visible: eqRect.state === "MAINHAND" || eqRect.state === "OFFHAND" || eqRect.state === "RANGED"

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

            visible: !scrollWeapon.visible

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

    RectangleBorders {
        width: parent.width - 850
        height: parent.height

        rectColor: root.darkDarkGray

        Image {
            x: parent.width / 2 - width / 2
            y: parent.height / 2 - height / 2

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
                    id: headSlot

                    state: eqRect.state
                    slotString: "HEAD"
                    iconSource: equipment.headIcon

                    onSelectItem: eqRect.state = "HEAD"
                }

                EquipmentSlotBox {
                    id: neckSlot

                    state: eqRect.state
                    slotString: "NECK"
                    iconSource: equipment.neckIcon

                    onSelectItem: eqRect.state = "NECK"
                }

                EquipmentSlotBox {
                    id: shoulderSlot

                    state: eqRect.state
                    slotString: "SHOULDERS"
                    iconSource: equipment.shouldersIcon

                    onSelectItem: eqRect.state = "SHOULDERS"
                }

                EquipmentSlotBox {
                    id: backSlot

                    state: eqRect.state
                    slotString: "BACK"
                    iconSource: equipment.backIcon

                    onSelectItem: eqRect.state = "BACK"
                }

                EquipmentSlotBox {
                    id: chestSlot

                    state: eqRect.state
                    slotString: "CHEST"
                    iconSource: equipment.chestIcon

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

                    state: eqRect.state
                    slotString: "WRIST"
                    iconSource: equipment.wristIcon

                    onSelectItem: eqRect.state = "WRIST"
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

                    state: eqRect.state
                    slotString: "GLOVES"
                    iconSource: equipment.glovesIcon

                    onSelectItem: eqRect.state = "GLOVES"
                }

                EquipmentSlotBox {
                    id: beltSlot

                    state: eqRect.state
                    slotString: "BELT"
                    iconSource: equipment.beltIcon

                    onSelectItem: eqRect.state = "BELT"
                }

                EquipmentSlotBox {
                    id: legSlot

                    state: eqRect.state
                    slotString: "LEGS"
                    iconSource: equipment.legsIcon

                    onSelectItem: eqRect.state = "LEGS"
                }

                EquipmentSlotBox {
                    id: bootSlot

                    state: eqRect.state
                    slotString: "BOOTS"
                    iconSource: equipment.bootsIcon

                    onSelectItem: eqRect.state = "BOOTS"
                }

                EquipmentSlotBox {
                    id: ring1Slot

                    state: eqRect.state
                    slotString: "RING1"
                    iconSource: equipment.ring1Icon

                    onSelectItem: eqRect.state = "RING1"
                }

                EquipmentSlotBox {
                    id: ring2Slot

                    state: eqRect.state
                    slotString: "RING2"
                    iconSource: equipment.ring2Icon

                    onSelectItem: eqRect.state = "RING2"
                }

                EquipmentSlotBox {
                    id: trinket1Slot

                    state: eqRect.state
                    slotString: "TRINKET1"
                    iconSource: equipment.trinket1Icon

                    onSelectItem: eqRect.state = "TRINKET1"
                }

                EquipmentSlotBox {
                    id: trinket2Slot

                    state: eqRect.state
                    slotString: "TRINKET2"
                    iconSource: equipment.trinket2Icon

                    onSelectItem: eqRect.state = "TRINKET2"
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

                    state: eqRect.state
                    slotString: "RANGED"
                    iconSource: equipment.rangedIcon

                    onSelectItem: eqRect.state = "RANGED"
                }
            }
        }
    }
}
