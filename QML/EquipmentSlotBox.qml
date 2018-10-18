import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    signal selectItem()
    signal showTooltip()
    signal hideTooltip()

    property string slotString
    property string iconSource: ""
    property string enchantOrientation: "None"
    property string enchantLayoutDirection: "DOWN"

    state: "MAINHAND"

    height: 46
    width: 46

    radius: 5
    color: "transparent"
    border.color: state === slotString ? root.gold : "transparent"
    border.width: 1

    Image {
        source: iconSource
        height: parent.height - 2
        width: parent.width - 2
        x: 1
        y: 1
    }

    MouseArea {
        anchors.fill: parent

        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: {
            if (mouse.button === Qt.RightButton)
                equipment.clearSlot(slotString);

            selectItem();
            equipment.selectSlot(slotString)
        }

        onEntered: showTooltip()
        onExited: hideTooltip()
    }

    EquipmentEnchant {
        id: enchant
        orientation: enchantOrientation
        layoutDirection: enchantLayoutDirection
        slot: slotString
    }

    EquipmentEnchant {
        id: temporaryEnchant
        orientation: enchantOrientation
        layoutDirection: enchantLayoutDirection
        slot: slotString
        temporaryEnchant: true

        anchors.top: enchant.bottom

        visible: (slotString === "MAINHAND" || slotString === "OFFHAND") && equipment.hasItemEquipped(slot)
    }


}
