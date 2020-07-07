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
        function onEquipmentChanged() {
            if (!temporaryEnchant)
                visible = orientation !== "None" && equipment.hasItemEquipped(slot)
            else
                visible = (slotString === "MAINHAND" || slotString === "OFFHAND") && equipment.hasItemEquipped(slot)
        }
        function onEnchantChanged() { setEffectText() }
    }

    function setEffectText() {
        hasEnchant = temporaryEnchant ? equipment.hasTemporaryEnchant(slot) : equipment.hasEnchant(slot)

        if (temporaryEnchant)
            effectText.text = hasEnchant ? equipment.getTemporaryEnchantEffect(slot) : ""
        else
            effectText.text = hasEnchant ? equipment.getEnchantEffect(slot) : ""
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

    TextSmall {
        id: effectText
        visible: text != ""

        text: setEffectText()

        elide: slot === "MAINHAND" ? Text.ElideRight : Text.ElideNone

        color: root.qualityUncommon
        horizontalAlignment: orientation === "LEFT" ? Text.AlignRight : Text.AlignLeft
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
                return mhTempEnchantModel
            }
            else
                return mhEnchantModel
        case "OFFHAND":
            if (temporaryEnchant === true)
                return ohTempEnchantModel
            else
                return ohEnchantModel
        case "RANGED":
            return rangedEnchantModel
        case "HEAD":
        case "LEGS":
            return headLegsEnchantModel
        case "SHOULDERS":
            return shoulderEnchantModel
        case "BACK":
            return backEnchantModel
        case "CHEST":
            return chestEnchantModel
        case "WRIST":
            return wristEnchantModel
        case "GLOVES":
            return glovesEnchantModel
        case "BOOTS":
            return bootsEnchantModel
        }

        return mhEnchantModel
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
                console.log("Clicked", _name)
                if (temporaryEnchant)
                    equipment.applyTemporaryEnchant(slot, _enum)
                else
                    equipment.applyEnchant(slot, _enum)
            }
            onRectangleRightClicked: {
                listView.visible = false
            }

            TextSmall {
                text: _name
            }
        }
    }
}
