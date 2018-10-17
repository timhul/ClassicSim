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
        width: parent.width - equipmentSlots.width
        anchors {
            right: parent.right
        }

        EquipmentFilters {
            id: filterRect
            anchors {
                left: parent.left
                leftMargin: 10
                top: parent.top
                topMargin: 10
                bottom: parent.bottom
            }

            onToggleStatFilterSelection: {
                statFilter.visible = !statFilter.visible
            }
        }

        Rectangle {
            id: modelViewRect
            anchors {
                left: filterRect.right
                leftMargin: 10
                top: parent.top
                bottom: parent.bottom
                right: parent.right
            }

            color: "transparent"

            EquipmentSortingWeapon {
                id: sortingWeaponRect
                visible: scrollWeapon.visible
            }

            EquipmentSortingItem {
                id: sortingItemRect
                visible: !scrollWeapon.visible
            }

            RectangleBorders {
                id: selectionRect
                anchors {
                    top: sortingWeaponRect.bottom
                    bottom: parent.bottom
                    left: parent.left
                    right: parent.right
                }

                ScrollView {
                    id: scrollWeapon
                    width: parent.width

                    visible: eqRect.state === "MAINHAND" || eqRect.state === "OFFHAND" || eqRect.state === "RANGED"

                    anchors.fill: parent
                    ScrollBar.vertical.policy: ScrollBar.AlwaysOn

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
                    anchors.fill: parent
                    visible: !scrollWeapon.visible
                    ScrollBar.vertical.policy: ScrollBar.AlwaysOn

                    ListView {
                        model: itemModel
                        boundsBehavior: Flickable.StopAtBounds

                        clip: true

                        delegate: ItemEntry {
                            entryName: name
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

                Row {
                    id: statFilter
                    anchors.fill: parent
                    visible: false

                    RectangleBorders {
                        id: statFilterView
                        height: parent.height
                        width: parent.width / 4

                        ScrollView {
                            anchors.fill: parent

                            ListView {
                                model: availableStatFilterModel
                                boundsBehavior: Flickable.StopAtBounds

                                clip: true

                                delegate: RectangleBorders {
                                    height: 30
                                    width: parent.width
                                    Text {
                                        text: description

                                        font {
                                            family: "Arial"
                                            pointSize: 9
                                        }

                                        anchors.fill: parent

                                        color: "white"
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                    }
                                    onRectangleClicked: {
                                        statFilter.visible = false
                                        availableStatFilterModel.addStatFilter(index)
                                    }
                                }
                            }
                        }
                    }

                    MouseArea {
                        height: parent.height
                        width: parent.width - statFilterView.width
                        onClicked: statFilter.visible = false
                    }
                }
            }
        }
    }

    RectangleBorders {
        id: equipmentSlots
        width: 500
        height: parent.height

        rectColor: root.darkDarkGray

        Image {
            x: parent.width / 2 - width / 2
            y: parent.height / 2 - height / 2

            source: "Assets/char_slots.png"

            height: 448
            width: 426

            CharacterStats {
                x: parent.width - width - 70
                y: parent.height - height - 65
            }

            Column {
                width: 46
                height: parent.height

                x: 12
                y: 7

                spacing: 5

                EquipmentSlotBox {
                    id: headSlot
                    enchantOrientation: "RIGHT"
                    z: 5

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
                    enchantOrientation: "RIGHT"
                    z: 3

                    state: eqRect.state
                    slotString: "SHOULDERS"
                    iconSource: equipment.shouldersIcon

                    onSelectItem: eqRect.state = "SHOULDERS"
                }

                EquipmentSlotBox {
                    id: backSlot
                    enchantOrientation: "RIGHT"
                    z: 2

                    state: eqRect.state
                    slotString: "BACK"
                    iconSource: equipment.backIcon

                    onSelectItem: eqRect.state = "BACK"
                }

                EquipmentSlotBox {
                    id: chestSlot
                    enchantOrientation: "RIGHT"
                    z: 1

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
                    enchantOrientation: "RIGHT"
                    enchantLayoutDirection: "UP"
                    z: 5

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
                    enchantOrientation: "BELOW"
                    enchantLayoutDirection: "UP"
                    z: 3

                    state: eqRect.state
                    slotString: "MAINHAND"
                    iconSource: equipment.mainhandIcon

                    onSelectItem: eqRect.state = "MAINHAND"
                }

                EquipmentSlotBox {
                    id: offhandSlot
                    enchantOrientation: "BELOW"
                    enchantLayoutDirection: "UP"
                    z: 2

                    state: eqRect.state
                    slotString: "OFFHAND"
                    iconSource: equipment.offhandIcon

                    onSelectItem: eqRect.state = "OFFHAND"
                }

                EquipmentSlotBox {
                    id: rangedSlot
                    enchantOrientation: "BELOW"
                    enchantLayoutDirection: "UP"
                    z: 1

                    state: eqRect.state
                    slotString: "RANGED"
                    iconSource: equipment.rangedIcon

                    onSelectItem: eqRect.state = "RANGED"
                }
            }
        }
    }
}
