import QtQuick 2.0

RectangleBorders {
    property bool slotEquipped: false

    id: ttRect

    Component.onCompleted: updateTooltip()

    Connections {
        target: equipment
        function onEquipmentChanged() { updateTooltip() }
    }

    function updateTooltip() {
        var tooltipInfo = equipment.getTooltip("PROJECTILE")
        if (tooltipInfo.length === 0) {
            slotEquipped = false;
            return;
        }

        slotEquipped = true;
        ttTitle.text = tooltipInfo[0];
        ttTitle.color = root.qualityColor(tooltipInfo[1]);

        ttBind.text = tooltipInfo[2];
        ttItemSlot.text = tooltipInfo[4];
        ttItemType.text = tooltipInfo[5];
        ttProjectileDps.text = tooltipInfo[8];
        ttLevelRequirement.text = tooltipInfo[11];

        ttRect.height = getTooltipHeight()
    }

    function getTooltipHeight() {
        var height = 0;
        height += ttTitle.contentHeight
        height += ttBind.contentHeight
        height += ttItemSlot.contentHeight
        height += ttProjectileDps.contentHeight
        height += ttLevelRequirement.contentHeight

        height += 20
        return height
    }

    visible: false

    width: 188

    rectColor: root.darkDarkGray
    opacity: 0.8
    setRadius: 4

    Text {
        id: ttTitle

        anchors {
            top: ttRect.top
            left: ttRect.left
            topMargin: 10
            leftMargin: 10
        }
        height : 15

        font {
            family: "Arial"
            pointSize: 10.5
        }

        visible: ttRect.visible

        color: root.qualityLegendary

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: ttBind

        anchors {
            top: ttTitle.bottom
            topMargin: 5
            left: ttRect.left
            leftMargin: 10
        }

        height: 10
        font {
            family: "Arial"
            pointSize: 9
        }

        visible: ttRect.visible

        color: "white"
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: ttItemSlot

        anchors {
            top: ttBind.visible === true ? ttBind.bottom : ttTitle.bottom
            topMargin: 5
            left: ttRect.left
            leftMargin: 10
        }

        height: 10
        font {
            family: "Arial"
            pointSize: 9
        }

        visible: ttRect.visible

        color: "white"
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: ttItemType

        anchors {
            top: ttBind.visible === true ? ttBind.bottom : ttTitle.bottom
            topMargin: 5
            right: ttRect.right
            rightMargin: 10
        }

        height: 10
        font {
            family: "Arial"
            pointSize: 9
        }

        visible: ttRect.visible

        color: "white"
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: ttProjectileDps

        anchors {
            top: ttItemSlot.bottom
            topMargin: 5
            left: ttRect.left
            leftMargin: 10
        }

        height: text !== "" ? 10 : 0
        font {
            family: "Arial"
            pointSize: 9
        }

        visible: ttRect.visible && text !== ""

        color: "white"
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: ttLevelRequirement

        anchors {
            top: ttProjectileDps.bottom
            topMargin: 5
            left: ttRect.left
            leftMargin: 10
        }

        font {
            family: "Arial"
            pointSize: 9
        }

        height: 10
        visible: ttRect.visible && text !== ""

        color: "white"
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }
}
