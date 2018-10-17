import QtQuick 2.0
import EnchantName 1.0

Rectangle {
    color: "transparent"
    height: 16
    width: 50
    property string orientation
    property string layoutDirection
    property string slot
    property bool hasEnchant: equipment.hasEnchant(slot)
    property bool temporaryEnchant: false

    visible: orientation !== "None" && equipment.hasItemEquipped(slot)

    Connections {
        target: equipment
        onEquipmentChanged: {
            visible = orientation !== "None" && equipment.hasItemEquipped(slot)
        }
        onEnchantChanged: {
            hasEnchant = equipment.hasEnchant(slot)

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
        if (orientation === "BELOW") {
            anchors.left = parent.left
            anchors.top = parent.bottom
            anchors.topMargin = 10
        }
    }

    Image {
        visible: parent.hasEnchant === false && parent.visible
        source: "Assets/misc/Trade_engraving.png"
        height: 16
        width: height
    }

    Text {
        id: effectText
        visible: text != ""

        text: ""

        font {
            family: "Arial"
            pointSize: 9
        }

        anchors.fill: parent

        color: root.qualityUncommon
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onClicked: {
            if (mouse.button === Qt.RightButton) {
                if (hasEnchant)
                    equipment.clearEnchant(slot)
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
            if (temporaryEnchant === true)
                return enchantTemporaryMHWeaponModel
            else
                return equipment.has2HWeapon ? enchant2HWeaponModel : enchant1HWeaponModel
        case "OFFHAND":
            if (temporaryEnchant === true)
                return enchantTemporaryOHWeaponModel
            else
                return enchant1HWeaponModel
        case "HEAD":
            return enchantHeadModel
        case "SHOULDERS":
            return enchantShoulderModel
        case "BACK":
            return enchantBackModel
        case "CHEST":
            return enchantChestModel
        case "WRIST":
            return enchantWristModel
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

            onRectangleClicked: {
                listView.visible = false
                console.log("Clicked", name)
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
        id: enchantTemporaryMHWeaponModel

        ListElement {
            name: "Windfury Totem"
            enumvalue: EnchantName.WindfuryTotem
        }
    }

    ListModel {
        id: enchantTemporaryOHWeaponModel

        ListElement {
            name: "<Placeholder>"
            enumvalue: EnchantName.Crusader
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
        id: enchantHeadModel

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
}
