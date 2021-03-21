import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    id: eqRect
    height: parent.height
    width: parent.width

    color: root.darkDarkGray
    property bool displayRangedWeapon: settings.className === "Warrior" ||
                                       settings.className === "Rogue" ||
                                       settings.className === "Hunter" ||
                                       settings.className === "Mage" ||
                                       settings.className === "Warlock" ||
                                       settings.className === "Priest"

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

            RectangleBorders {
                id: search

                height: 35

                anchors {
                    top: parent.top
                    left: parent.left
                    right: parent.right
                }

                TextInput {
                    anchors {
                        fill: parent
                        leftMargin: 10
                        topMargin: 8
                    }

                    onFocusChanged: {
                        if (activeFocus)
                            selectAll()
                        else
                            deselect()
                    }

                    onTextChanged: scrollWeapon.visible ? weaponModel.lexicalSearch(text) : itemModel.lexicalSearch(text)

                    Keys.onReturnPressed: {
                        if (activeFocus)
                            focus = false
                    }

                    color: "white"
                    selectedTextColor: "black"
                    selectionColor: "white"
                    text: "Search..."
                    font {
                        pointSize: 12
                    }
                }
            }

            EquipmentSortingWeapon {
                id: sortingWeaponRect
                visible: scrollWeapon.visible

                anchors.top: search.bottom
            }

            EquipmentSortingItem {
                id: sortingItemRect
                visible: !scrollWeapon.visible

                anchors.top: search.bottom
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

                    visible: eqRect.state === "MAINHAND" || eqRect.state === "OFFHAND" || (eqRect.state === "RANGED" && eqRect.displayRangedWeapon)

                    anchors.fill: parent
                    ScrollBar.vertical.policy: ScrollBar.AlwaysOn

                    ListView {
                        id: weaponListView
                        model: weaponModel
                        boundsBehavior: Flickable.StopAtBounds

                        clip: true

                        delegate: ItemEntryWeapon {
                            itemid: _itemid
                            entryName: _name
                            entrySpeed: _speed
                            entryDps: _dps
                            entryPhase: _phase
                            entrySource: _source
                            entryType: _type
                            entryReq: _reqlvl
                            entryItemlvl: _itemlvl
                            entryQuality: _quality
                            entryIcon: _icon
                            entryRandomAffix: _randomaffix

                            onEntryClicked: {
                                if (entryRandomAffix) {
                                    equipment.setRandomAffixesModelId(itemid)
                                    randomWeaponPopup.x = mouseX
                                    randomWeaponPopup.y = mouseY
                                    randomWeaponPopup.open()
                                }
                                else {
                                    equipment.setSlot(eqRect.state, itemid)
                                }
                            }

                            onShowTooltip: {
                                weaponTooltip.itemId = itemid
                                weaponTooltip.updateTooltip()
                                weaponTooltip.visible = true;
                            }

                            onUpdateTooltip: {
                                var pos = mapToItem(weaponListView, mouseX, mouseY)
                                weaponTooltip.x = pos.x > weaponListView.width / 2 ? pos.x - 12 - weaponTooltip.width : pos.x + 12
                                weaponTooltip.y = pos.y > weaponListView.height / 2 ? pos.y - weaponTooltip.getTooltipHeight() : pos.y
                            }

                            onHideTooltip: {
                                weaponTooltip.visible = false;
                            }

                            Popup {
                                id: randomWeaponPopup
                                padding: 1
                                width: 300
                                contentHeight: weaponRandomAffixesList.contentHeight

                                RandomAffixesList {
                                    id: weaponRandomAffixesList

                                    onEntryClicked: {
                                        randomWeaponPopup.close()
                                        equipment.setSlot(eqRect.state, itemid, affixId)
                                    }
                                }
                            }
                        }

                        EquipmentTooltip {
                            id: weaponTooltip
                            useId: true
                        }
                    }
                }

                ScrollView {
                    anchors.fill: parent
                    visible: !scrollWeapon.visible
                    ScrollBar.vertical.policy: ScrollBar.AlwaysOn

                    clip: true

                    ListView {
                        id: itemListView
                        model: itemModel
                        boundsBehavior: Flickable.StopAtBounds

                        clip: true

                        delegate: ItemEntry {
                            itemid: _itemid
                            entryName: _name
                            entryPhase: _phase
                            entrySource: _source
                            entryType: _type
                            entryReq: _reqlvl
                            entryItemlvl: _itemlvl
                            entryQuality: _quality
                            entryIcon: _icon
                            entryRandomAffix: _randomaffix

                            onEntryClicked: {
                                if (entryRandomAffix) {
                                    equipment.setRandomAffixesModelId(itemid)
                                    randomEquipmentPopup.x = mouseX
                                    randomEquipmentPopup.y = mouseY
                                    randomEquipmentPopup.open()
                                }
                                else {
                                    equipment.setSlot(eqRect.state, itemid)
                                }
                            }

                            onShowTooltip: {
                                itemTooltip.itemId = itemid
                                itemTooltip.updateTooltip()
                                itemTooltip.visible = true;
                            }

                            onUpdateTooltip: {
                                var pos = mapToItem(itemListView, mouseX, mouseY)
                                itemTooltip.x = pos.x > itemListView.width / 2 ? pos.x - 12 - itemTooltip.width : pos.x + 12
                                itemTooltip.y = pos.y > itemListView.height / 2 ? pos.y - itemTooltip.getTooltipHeight() : pos.y
                            }

                            onHideTooltip: {
                                itemTooltip.visible = false;
                            }

                            Popup {
                                id: randomEquipmentPopup
                                padding: 1
                                width: 300
                                contentHeight: equipmentRandomAffixesList.contentHeight

                                RandomAffixesList {
                                    id: equipmentRandomAffixesList

                                    onEntryClicked: {
                                        randomEquipmentPopup.close()
                                        equipment.setSlot(eqRect.state, itemid, affixId)
                                    }
                                }
                            }
                        }

                        EquipmentTooltip {
                            id: itemTooltip
                            useId: true
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
                                    TextSmall {
                                        text: description
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

            property int spacing: 5
            property int leftOffset: 12

            EquipmentSlotBox {
                id: headSlot

                anchors {
                    left: parent.left
                    leftMargin: parent.leftOffset
                    top: parent.top
                    topMargin: 7
                }

                enchantOrientation: "RIGHT"
                z: 5

                state: eqRect.state
                slotString: "HEAD"
                iconSource: equipment.headIcon

                onSelectItem: eqRect.state = "HEAD"

                onShowTooltip: headTT.visible = headTT.slotEquipped
                onHideTooltip: headTT.visible = false
            }

            EquipmentTooltip {
                id: headTT
                slotString: headSlot.slotString
                z: 10

                anchors {
                    left: headSlot.right
                    top: headSlot.top
                    topMargin: height > 450 ? 450 - height : 0
                }
            }

            EquipmentSlotBox {
                id: neckSlot

                anchors {
                    left: headSlot.left
                    top: headSlot.bottom
                    topMargin: parent.spacing
                }

                state: eqRect.state
                slotString: "NECK"
                iconSource: equipment.neckIcon

                onSelectItem: eqRect.state = "NECK"

                onShowTooltip: neckTT.visible = neckTT.slotEquipped
                onHideTooltip: neckTT.visible = false
            }

            EquipmentTooltip {
                id: neckTT
                slotString: neckSlot.slotString
                z: 10

                anchors {
                    left: neckSlot.right
                    top: neckSlot.top
                    topMargin: height > 450 ? 450 - height : 0
                }
            }

            EquipmentSlotBox {
                id: shoulderSlot
                enchantOrientation: "RIGHT"
                z: 3

                anchors {
                    left: neckSlot.left
                    top: neckSlot.bottom
                    topMargin: parent.spacing
                }

                state: eqRect.state
                slotString: "SHOULDERS"
                iconSource: equipment.shouldersIcon

                onSelectItem: eqRect.state = "SHOULDERS"

                onShowTooltip: shoulderTT.visible = shoulderTT.slotEquipped
                onHideTooltip: shoulderTT.visible = false
            }

            EquipmentTooltip {
                id: shoulderTT
                slotString: shoulderSlot.slotString
                z: 10

                anchors {
                    left: shoulderSlot.right
                    top: shoulderSlot.top
                    topMargin: height > 348 ? 348 - height : 0
                }
            }

            EquipmentSlotBox {
                id: backSlot
                enchantOrientation: "RIGHT"
                z: 2

                anchors {
                    left: shoulderSlot.left
                    top: shoulderSlot.bottom
                    topMargin: parent.spacing
                }

                state: eqRect.state
                slotString: "BACK"
                iconSource: equipment.backIcon

                onSelectItem: eqRect.state = "BACK"

                onShowTooltip: backTT.visible = backTT.slotEquipped
                onHideTooltip: backTT.visible = false
            }

            EquipmentTooltip {
                id: backTT
                slotString: backSlot.slotString
                z: 10

                anchors {
                    left: backSlot.right
                    bottom: backSlot.top
                }
            }

            EquipmentSlotBox {
                id: chestSlot
                enchantOrientation: "RIGHT"
                z: 1

                anchors {
                    left: backSlot.left
                    top: backSlot.bottom
                    topMargin: parent.spacing
                }

                state: eqRect.state
                slotString: "CHEST"
                iconSource: equipment.chestIcon

                onSelectItem: eqRect.state = "CHEST"

                onShowTooltip: chestTT.visible = chestTT.slotEquipped
                onHideTooltip: chestTT.visible = false
            }

            EquipmentTooltip {
                id: chestTT
                slotString: chestSlot.slotString
                z: 10

                anchors {
                    left: chestSlot.right
                    top: chestSlot.top
                    topMargin: height > 246 ? 246 - height : 0
                }
            }

            EquipmentSlotBox {
                id: shirtSlot

                anchors {
                    left: chestSlot.left
                    top: chestSlot.bottom
                    topMargin: parent.spacing
                }
            }

            EquipmentSlotBox {
                id: tabardSlot

                anchors {
                    left: shirtSlot.left
                    top: shirtSlot.bottom
                    topMargin: parent.spacing
                }
            }

            EquipmentSlotBox {
                id: wristSlot

                anchors {
                    left: tabardSlot.left
                    top: tabardSlot.bottom
                    topMargin: parent.spacing
                }

                enchantOrientation: "RIGHT"
                enchantLayoutDirection: "UP"
                z: 5

                state: eqRect.state
                slotString: "WRIST"
                iconSource: equipment.wristIcon

                onSelectItem: eqRect.state = "WRIST"

                onShowTooltip: wristTT.visible = wristTT.slotEquipped
                onHideTooltip: wristTT.visible = false
            }

            EquipmentTooltip {
                id: wristTT
                slotString: wristSlot.slotString
                z: 10

                anchors {
                    left: wristSlot.right
                    bottom: wristSlot.top
                    bottomMargin: height > 450 ? 450 - height : 0
                }
            }

            EquipmentSlotBox {
                id: ammoSlot
                height: 34
                width: 34

                x: 255
                y: 398
                state: eqRect.state
                slotString: "PROJECTILE"
                iconSource: equipment.projectileIcon

                onSelectItem: eqRect.state = "PROJECTILE"

                onShowTooltip: ammoTT.visible = ammoTT.slotEquipped
                onHideTooltip: ammoTT.visible = false
            }

            EquipmentTooltipProjectile {
                id: ammoTT
                z: 10

                anchors {
                    left: ammoSlot.right
                    bottom: ammoSlot.top
                    bottomMargin: height > 450 ? 450 - height : 0
                }
            }

            Column {
                width: 46
                height: parent.height

                x: 367
                y: 7

                spacing: 5

                EquipmentSlotBox {
                    id: gloveSlot
                    enchantOrientation: "LEFT"
                    z: 3

                    state: eqRect.state
                    slotString: "GLOVES"
                    iconSource: equipment.glovesIcon

                    onSelectItem: eqRect.state = "GLOVES"

                    onShowTooltip: glovesTT.visible = glovesTT.slotEquipped
                    onHideTooltip: glovesTT.visible = false

                    EquipmentTooltip {
                        id: glovesTT
                        slotString: parent.slotString

                        anchors {
                            left: parent.right
                            top: parent.top
                            topMargin: height > 450 ? 450 - height : 0
                        }
                    }
                }

                EquipmentSlotBox {
                    id: beltSlot

                    state: eqRect.state
                    slotString: "BELT"
                    iconSource: equipment.beltIcon

                    onSelectItem: eqRect.state = "BELT"

                    onShowTooltip: beltTT.visible = beltTT.slotEquipped
                    onHideTooltip: beltTT.visible = false

                    EquipmentTooltip {
                        id: beltTT
                        slotString: parent.slotString

                        anchors {
                            left: parent.right
                            top: parent.top
                            topMargin: height > 399 ? 399 - height : 0
                        }
                    }
                }

                EquipmentSlotBox {
                    id: legSlot
                    enchantOrientation: "LEFT"
                    z: 2

                    state: eqRect.state
                    slotString: "LEGS"
                    iconSource: equipment.legsIcon

                    onSelectItem: eqRect.state = "LEGS"

                    onShowTooltip: legsTT.visible = legsTT.slotEquipped
                    onHideTooltip: legsTT.visible = false

                    EquipmentTooltip {
                        id: legsTT
                        slotString: parent.slotString

                        anchors {
                            left: parent.right
                            top: parent.top
                            topMargin: height > 348 ? 348 - height : 0
                        }
                    }
                }

                EquipmentSlotBox {
                    id: bootSlot
                    enchantOrientation: "LEFT"
                    z: 1

                    state: eqRect.state
                    slotString: "BOOTS"
                    iconSource: equipment.bootsIcon

                    onSelectItem: eqRect.state = "BOOTS"

                    onShowTooltip: bootsTT.visible = bootsTT.slotEquipped
                    onHideTooltip: bootsTT.visible = false

                    EquipmentTooltip {
                        id: bootsTT
                        slotString: parent.slotString

                        anchors {
                            left: parent.right
                            top: parent.top
                            topMargin: height > 297 ? 297 - height : 0
                        }
                    }
                }

                EquipmentSlotBox {
                    id: ring1Slot

                    state: eqRect.state
                    slotString: "RING1"
                    iconSource: equipment.ring1Icon

                    onSelectItem: eqRect.state = "RING1"

                    onShowTooltip: ring1TT.visible = ring1TT.slotEquipped
                    onHideTooltip: ring1TT.visible = false

                    EquipmentTooltip {
                        id: ring1TT
                        slotString: parent.slotString

                        anchors {
                            left: parent.right
                            top: parent.top
                            topMargin: height > 246 ? 246 - height : 0
                        }
                    }
                }

                EquipmentSlotBox {
                    id: ring2Slot

                    state: eqRect.state
                    slotString: "RING2"
                    iconSource: equipment.ring2Icon

                    onSelectItem: eqRect.state = "RING2"

                    onShowTooltip: ring2TT.visible = ring2TT.slotEquipped
                    onHideTooltip: ring2TT.visible = false

                    EquipmentTooltip {
                        id: ring2TT
                        slotString: parent.slotString

                        anchors {
                            left: parent.right
                            top: parent.top
                            topMargin: height > 195 ? 195 - height : 0
                        }
                    }
                }

                EquipmentSlotBox {
                    id: trinket1Slot

                    state: eqRect.state
                    slotString: "TRINKET1"
                    iconSource: equipment.trinket1Icon

                    onSelectItem: eqRect.state = "TRINKET1"

                    onShowTooltip: trinket1TT.visible = trinket1TT.slotEquipped
                    onHideTooltip: trinket1TT.visible = false

                    EquipmentTooltip {
                        id: trinket1TT
                        slotString: parent.slotString

                        anchors {
                            bottom: parent.top
                            left: parent.right
                        }
                    }
                }

                EquipmentSlotBox {
                    id: trinket2Slot

                    state: eqRect.state
                    slotString: "TRINKET2"
                    iconSource: equipment.trinket2Icon

                    onSelectItem: eqRect.state = "TRINKET2"

                    onShowTooltip: trinket2TT.visible = trinket2TT.slotEquipped
                    onHideTooltip: trinket2TT.visible = false

                    EquipmentTooltip {
                        id: trinket2TT
                        slotString: parent.slotString

                        anchors {
                            bottom: parent.top
                            left: parent.right
                        }
                    }
                }
            }

            Row {
                height: 46
                width: 46*3 + 12

                x: 85
                y: 393

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

                    onShowTooltip: mhTT.visible = mhTT.slotEquipped
                    onHideTooltip: mhTT.visible = false

                    EquipmentTooltip {
                        id: mhTT
                        slotString: parent.slotString

                        anchors {
                            bottom: parent.top
                            left: parent.right
                        }
                    }
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

                    onShowTooltip: ohTT.visible = ohTT.slotEquipped
                    onHideTooltip: ohTT.visible = false

                    EquipmentTooltip {
                        id: ohTT
                        slotString: parent.slotString

                        anchors {
                            bottom: parent.top
                            left: parent.right
                        }
                    }
                }

                EquipmentSlotBox {
                    id: rangedSlot
                    enchantOrientation: "BELOW"
                    enchantLayoutDirection: "UP"
                    z: 1

                    state: eqRect.state
                    slotString: eqRect.displayRangedWeapon ? "RANGED" : "RELIC"
                    iconSource: eqRect.displayRangedWeapon ? equipment.rangedIcon : equipment.relicIcon

                    onSelectItem: eqRect.state = slotString

                    onShowTooltip: rangedTT.visible = rangedTT.slotEquipped
                    onHideTooltip: rangedTT.visible = false

                    EquipmentTooltip {
                        id: rangedTT
                        slotString: parent.slotString

                        anchors {
                            bottom: parent.top
                            left: parent.right
                        }
                    }
                }

            }

            EquipmentSlotBox {
                id: quiverSlot

                x: 302
                y: 393
                state: eqRect.state
                slotString: "QUIVER"
                iconSource: equipment.quiverIcon

                onSelectItem: eqRect.state = "QUIVER"

                onShowTooltip: quiverTooltip.visible = quiverTooltip.slotEquipped
                onHideTooltip: quiverTooltip.visible = false

                EquipmentTooltip {
                    id: quiverTooltip
                    slotString: parent.slotString

                    anchors {
                        bottom: parent.top
                        left: parent.right
                    }
                }
            }
        }
    }
}
