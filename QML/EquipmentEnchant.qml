import QtQuick 2.0
import EnchantName 1.0

Rectangle {
    color: "transparent"
    height: 16
    width: 100
    property string orientation
    property string slot
    property bool hasEnchant: equipment.hasEnchant(slot)

    visible: orientation === "RIGHT" && equipment.hasItemEquipped(slot)

    Connections {
        target: equipment
        onEquipmentChanged: {
            visible = orientation === "RIGHT" && equipment.hasItemEquipped(slot)
        }
        onEnchantChanged: {
            hasEnchant = equipment.hasEnchant(slot)

            effectText.text = hasEnchant ? equipment.getEnchantEffect(slot) : ""
        }
    }

    anchors {
        left: parent.right
        leftMargin: 13
        bottom: parent.bottom
        bottomMargin: 3
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
            if (mouse.button === Qt.RightButton)
                equipment.clearEnchant(slot)
            else
                listView.visible = !listView.visible
        }
    }

    function getModelFromSlot() {
        switch (slot) {
        case "MAINHAND":
            return equipment.has2HWeapon ? enchant2HWeaponModel : enchant1HWeaponModel
        case "OFFHAND":
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
        anchors.top: parent.bottom
        id: listView
        interactive: false
        width: parent.width
        visible: false
        implicitHeight: contentHeight
        implicitWidth: contentWidth

        model: getModelFromSlot()
        delegate: RectangleBorders {
            height: 30
            width: 200

            onRectangleClicked: {
                listView.visible = false
                console.log("Clicked", name)
                equipment.applyEnchant(slot, enumvalue)
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
