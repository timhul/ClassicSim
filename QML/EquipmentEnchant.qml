import QtQuick 2.0
import EnchantName 1.0

Rectangle {
    color: "transparent"
    height: 16
    width: 50
    property string orientation
    property string layoutDirection
    property string slot
    property bool temporaryEnchant: false
    property bool hasEnchant: temporaryEnchant ? equipment.hasTemporaryEnchant(slot) : equipment.hasEnchant(slot)

    visible: orientation !== "None" && equipment.hasItemEquipped(slot)

    Connections {
        target: equipment
        onEquipmentChanged: {
            visible = orientation !== "None" && equipment.hasItemEquipped(slot)
        }
        onEnchantChanged: {
            hasEnchant = temporaryEnchant ? equipment.hasTemporaryEnchant(slot) : equipment.hasEnchant(slot)

            if (temporaryEnchant)
                effectText.text = hasEnchant ? equipment.getTemporaryEnchantEffect(slot) : ""
            else
                effectText.text = hasEnchant ? equipment.getEnchantEffect(slot) : ""
        }
    }

    Component.onCompleted: setAnchors()

    function setAnchors() {
        if (temporaryEnchant)
            return

        if (orientation === "RIGHT") {
            anchors.left = parent.right
            anchors.leftMargin = 13
            anchors.bottom = parent.bottom
            anchors.bottomMargin = 3
            }
        else if (orientation === "BELOW") {
            anchors.left = parent.left
            anchors.top = parent.bottom
            anchors.topMargin = 10
        }
        else if (orientation === "LEFT") {
            anchors.right = parent.left
            anchors.rightMargin = 13
            anchors.bottom = parent.bottom
            anchors.bottomMargin = 3
        }

        icon.setIconAnchors()
    }

    Image {
        id: icon
        visible: parent.hasEnchant === false && parent.visible
        source: "Assets/misc/Trade_engraving.png"
        height: 16
        width: height

        function setIconAnchors() {
            if (orientation === "LEFT") {
                anchors.right = parent.right
            }
        }
    }

    Text {
        id: effectText
        visible: text != ""

        text: ""

        elide: slot === "MAINHAND" ? Text.ElideRight : Text.ElideNone

        font {
            family: "Arial"
            pointSize: 9
        }

        anchors.fill: parent

        color: root.qualityUncommon
        horizontalAlignment: orientation === "LEFT" ? Text.AlignRight : Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onClicked: {
            if (mouse.button === Qt.RightButton) {
                if (hasEnchant) {
                    if (temporaryEnchant)
                        equipment.clearTemporaryEnchant(slot)
                    else
                        equipment.clearEnchant(slot)
                }
                else
                    listView.visible = false
            }
            else
                listView.visible = !listView.visible
        }
    }

    function getModelFromSlot() {
        switch (slot) {
        case "MAINHAND":
            if (temporaryEnchant === true) {
                if (character.isHorde)
                    return enchantTemporaryMHWeaponModelHorde
                else
                    return enchantTemporaryMHWeaponModelAlliance
            }
            else
                return equipment.has2HWeapon ? enchant2HWeaponModel : enchant1HWeaponModel
        case "OFFHAND":
            if (temporaryEnchant === true)
                return enchantTemporaryOHWeaponModel
            else
                return enchant1HWeaponModel
        case "HEAD":
        case "LEGS":
            return enchantHeadLegsModel
        case "SHOULDERS":
            return enchantShoulderModel
        case "BACK":
            return enchantBackModel
        case "CHEST":
            return enchantChestModel
        case "WRIST":
            return enchantWristModel
        case "GLOVES":
            return enchantGlovesModel
        case "BOOTS":
            return enchantBootsModel
        }

        return enchant2HWeaponModel
    }

    ListView {
        function setAnchors() {
            if (parent.layoutDirection === "DOWN")
                anchors.top = parent.bottom
            else
                anchors.bottom = parent.top
        }

        onVisibleChanged: {
            if (visible === true)
                setAnchors()
        }

        id: listView
        interactive: false
        width: parent.width
        visible: false
        implicitHeight: contentHeight
        implicitWidth: contentWidth

        verticalLayoutDirection: parent.layoutDirection === "DOWN" ? ListView.TopToBottom : ListView.BottomToTop

        model: getModelFromSlot()
        delegate: RectangleBorders {
            height: 30
            width: 200

            anchors.right: orientation === "LEFT" ? parent.right : undefined

            onRectangleClicked: {
                listView.visible = false
                console.log("Clicked", name)
                if (temporaryEnchant)
                    equipment.applyTemporaryEnchant(slot, enumvalue)
                else
                    equipment.applyEnchant(slot, enumvalue)
            }
            onRectangleRightClicked: {
                listView.visible = false
            }

            Text {
                anchors.fill: parent
                text: name

                font {
                    family: "Arial"
                    pointSize: 9
                }

                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

    ListModel {
        id: enchant1HWeaponModel

        ListElement {
            name: "Crusader"
            enumvalue: EnchantName.Crusader
        }

        ListElement {
            name: "Fiery Weapon"
            enumvalue: EnchantName.FieryWeapon
        }
    }

    ListModel {
        id: enchantTemporaryMHWeaponModelHorde

        ListElement {
            name: "Windfury Totem"
            enumvalue: EnchantName.WindfuryTotem
        }

        ListElement {
            name: "Elemental Sharpening Stone"
            enumvalue: EnchantName.ElementalSharpeningStone
        }
    }

    ListModel {
        id: enchantTemporaryMHWeaponModelAlliance

        ListElement {
            name: "Elemental Sharpening Stone"
            enumvalue: EnchantName.ElementalSharpeningStone
        }
    }

    ListModel {
        id: enchantTemporaryOHWeaponModel

        ListElement {
            name: "Elemental Sharpening Stone"
            enumvalue: EnchantName.ElementalSharpeningStone
        }
    }

    ListModel {
        id: enchant2HWeaponModel

        ListElement {
            name: "Iron Counterweight"
            enumvalue: EnchantName.IronCounterweight
        }

        ListElement {
            name: "Enchant 2H Weapon - Agility"
            enumvalue: EnchantName.Enchant2HWeaponAgility
        }

        ListElement {
            name: "Crusader"
            enumvalue: EnchantName.Crusader
        }

        ListElement {
            name: "Fiery Weapon"
            enumvalue: EnchantName.FieryWeapon
        }
    }

    ListModel {
        id: enchantHeadLegsModel

        ListElement {
            name: "Arcanum of Rapidity"
            enumvalue: EnchantName.ArcanumOfRapidity
        }

        ListElement {
            name: "Lesser Arcanum of Voracity"
            enumvalue: EnchantName.LesserArcanumOfVoracity
        }
    }

    ListModel {
        id: enchantShoulderModel

        ListElement {
            name: "Zandalar Signet of Might"
            enumvalue: EnchantName.ZandalarSignetOfMight
        }

        ListElement {
            name: "Might of the Scourge"
            enumvalue: EnchantName.MightOfTheScourge
        }
    }

    ListModel {
        id: enchantBackModel

        ListElement {
            name: "Enchant Cloak - Lesser Agility"
            enumvalue: EnchantName.EnchantCloakLesserAgility
        }
    }

    ListModel {
        id: enchantChestModel

        ListElement {
            name: "Enchant Chest - Greater Stats"
            enumvalue: EnchantName.EnchantChestGreaterStats
        }
    }

    ListModel {
        id: enchantWristModel

        ListElement {
            name: "Enchant Bracer - Superior Strength"
            enumvalue: EnchantName.EnchantBracerSuperiorStrength
        }
    }

    ListModel {
        id: enchantGlovesModel

        ListElement {
            name: "Enchant Gloves - Greater Strength"
            enumvalue: EnchantName.EnchantGlovesGreaterStrength
        }

        ListElement {
            name: "Enchant Gloves - Minor Haste"
            enumvalue: EnchantName.EnchantGlovesMinorHaste
        }
    }

    ListModel {
        id: enchantBootsModel

        ListElement {
            name: "Enchant Boots - Minor Speed"
            enumvalue: EnchantName.EnchantBootsMinorSpeed
        }

        ListElement {
            name: "Enchant Boots - Greater Agility"
            enumvalue: EnchantName.EnchantBootsGreaterAgility
        }
    }
}
