import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    signal selectItem();

    property string slotString
    property string iconSource: ""
    property bool slotEquipped: false
    property bool showTypeInTooltip: slotString !== "NECK" && slotString !== "RING1" && slotString !== "RING2"
                                     && slotString !== "TRINKET1" && slotString !== "TRINKET2"
    property bool showDurabilityInTooltip: showTypeInTooltip

    state: "MAINHAND"

    height: 46
    width: 46

    radius: 5
    color: "transparent"
    border.color: state === slotString ? root.gold : "transparent"
    border.width: 1

    Connections {
        target: equipment
        onEquipmentChanged: updateTooltip()
    }

    function updateTooltip() {
        var tooltipInfo = equipment.getTooltip(slotString)
        if (tooltipInfo.length === 0) {
            slotEquipped = false;
            return;
        }

        slotEquipped = true;
        ttTitle.text = tooltipInfo[0];
        ttTitle.color = root.qualityColor(tooltipInfo[1]);

        ttBind.text = tooltipInfo[2];
        ttUnique.text = tooltipInfo[3];
        ttItemSlot.text = tooltipInfo[4];
        ttItemType.text = tooltipInfo[5];
        ttItemType.visible = ttItemType.text !== "" && showTypeInTooltip
        ttWeaponDamageRange.text = tooltipInfo[6];
        ttWeaponSpeed.text = tooltipInfo[7];
        ttWeaponDps.text = tooltipInfo[8];
        ttBaseStats.text = tooltipInfo[9];
        ttClassRestrictions.text = tooltipInfo[10];
        ttLevelRequirement.text = tooltipInfo[11];
        ttEquipEffect.text = tooltipInfo[12];

        ttRect.height = getTooltipHeight()
    }

    function clearTooltip() {
        ttTitle.text = ""
    }

    function getTooltipHeight() {
        var height = 0;
        height += ttTitle.contentHeight + ttTitle.anchors.topMargin
        height += ttBind.contentHeight + ttBind.anchors.topMargin
        height += ttUnique.text !== "" ? ttUnique.contentHeight + ttUnique.anchors.topMargin : 0
        height += ttItemSlot.contentHeight + ttItemSlot.anchors.topMargin
        height += ttWeaponDamageRange.text !== "" ? (ttWeaponDamageRange.contentHeight + ttWeaponDamageRange.anchors.topMargin) * 2 : 0
        height += ttDurability.text !== "" ? ttDurability.contentHeight + ttDurability.anchors.topMargin : 0
        height += ttBaseStats.text !== "" ? ttBaseStats.contentHeight + ttBaseStats.anchors.topMargin : 0
        height += ttClassRestrictions.text !== "" ? ttClassRestrictions.contentHeight + ttClassRestrictions.anchors.topMargin : 0
        height += ttLevelRequirement.contentHeight + ttLevelRequirement.anchors.topMargin
        height += ttEquipEffect.text !== "" ? ttEquipEffect.contentHeight + ttEquipEffect.anchors.topMargin : 0

        height += 10
        return height
    }

    Component.onCompleted: updateTooltip()

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

        onEntered: {
            ttRect.visible = slotEquipped
        }
        onExited: {
            ttRect.visible = false
        }
    }

    RectangleBorders {
        id: ttRect
        anchors {
            left: parent.right
            bottom: parent.top
        }

        visible: false

        width: ttTitle.width > ttEquipEffect.width ? ttTitle.width + 20 :
                                                     ttEquipEffect.width +  20

        Component.onCompleted: getTooltipHeight()

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

            height: 15
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
            id: ttUnique

            anchors {
                top: ttBind.bottom
                topMargin: 5
                left: ttRect.left
                leftMargin: 10
            }

            height: 15
            font {
                family: "Arial"
                pointSize: 9
            }

            visible: ttRect.visible && text !== ""

            color: "white"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: ttItemSlot

            anchors {
                top: ttUnique.visible === true ? ttUnique.bottom : ttBind.bottom
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
                top: ttUnique.visible === true ? ttUnique.bottom : ttBind.bottom
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
            id: ttWeaponDamageRange

            anchors {
                top: ttItemSlot.bottom
                topMargin: 5
                left: ttRect.left
                leftMargin: 10
            }

            height: 10
            font {
                family: "Arial"
                pointSize: 9
            }

            visible: ttRect.visible && text !== ""

            color: "white"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: ttWeaponSpeed

            anchors {
                top: ttItemType.bottom
                topMargin: 5
                right: ttRect.right
                rightMargin: 10
            }

            height: 10
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
            id: ttWeaponDps

            anchors {
                top: ttWeaponDamageRange.bottom
                topMargin: 5
                left: ttRect.left
                leftMargin: 10
            }

            height: 10
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
            id: ttBaseStats

            anchors {
                top: ttWeaponDps.visible ? ttWeaponDps.bottom :
                                           ttItemSlot.bottom
                topMargin: 5
                left: ttRect.left
                leftMargin: 10
            }

            font {
                family: "Arial"
                pointSize: 9
            }

            visible: ttRect.visible && text !== ""

            color: "white"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: ttDurability

            anchors {
                top: ttBaseStats.visible ? ttBaseStats.bottom :
                                           ttWeaponDps.visible ? ttWeaponDps.bottom :
                                                                 ttItemSlot.bottom
                topMargin: 5
                left: ttRect.left
                leftMargin: 10
            }

            font {
                family: "Arial"
                pointSize: 9
            }

            text: "Durability 105 / 105"

            visible: ttRect.visible && showDurabilityInTooltip

            color: "white"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: ttClassRestrictions

            anchors {
                top: ttDurability.bottom
                topMargin: 5
                left: ttRect.left
                leftMargin: 10
            }

            font {
                family: "Arial"
                pointSize: 9
            }


            height: visible ? 10 : 0
            visible: ttRect.visible && text !== ""

            color: "white"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: ttLevelRequirement

            anchors {
                top: ttClassRestrictions.bottom
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

        Text {
            id: ttEquipEffect

            anchors {
                top: ttLevelRequirement.bottom
                left: ttRect.left
                topMargin: 3
                leftMargin: 10
            }

            width: Text.width < 280 ? Text.width:
                                      280

            font {
                family: "Arial"
                pointSize: 9
            }

            visible: ttRect.visible && text !== ""
            color: root.qualityUncommon
            wrapMode: Text.WordWrap

            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }
    }
}
