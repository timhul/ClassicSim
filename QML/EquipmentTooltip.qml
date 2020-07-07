import QtQuick 2.0

RectangleBorders {
    property string slotString
    property int itemId
    property bool useId: false

    property bool showDurabilityInTooltip: hasDurability()
    property bool showTypeInTooltip: showDurabilityInTooltip
    property bool slotEquipped: false

    id: ttRect

    Component.onCompleted: updateTooltip()

    Connections {
        target: equipment
        function onEquipmentChanged() { updateTooltip() }
    }

    function hasDurability() {
        switch (slotString) {
        case "BACK":
        case "NECK":
        case "RING1":
        case "RING2":
        case "TRINKET1":
        case "TRINKET2":
        case "RELIC":
            return false;
        default:
            return true;
        }
    }

    function updateTooltip() {
        var tooltipInfo = useId ? equipment.getTooltip(itemId) : equipment.getTooltip(slotString)
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
        ttFlavourText.text = tooltipInfo[13];

        if (tooltipInfo[14] === false) {
            ttSetName.text = ""
            ttSetItems.text = ""
            ttSetBonuses.text = ""
            ttRect.height = getTooltipHeight()
            return
        }

        ttSetName.text = tooltipInfo[15]
        var numSetPieces = tooltipInfo[16]
        var offset = 17
        var setPiecesText = " "
        for (var i = 0; i < numSetPieces; ++i) {
            setPiecesText += tooltipInfo[i + offset]
            if (i + 1 !== numSetPieces)
                setPiecesText += "<br> "
        }
        ttSetItems.text = setPiecesText

        offset += numSetPieces

        var numSetBonuses = tooltipInfo[offset]
        offset++
        var setBonusText = ""
        for (i = 0; i < numSetBonuses; ++i) {
            setBonusText += tooltipInfo[i + offset]
            if (i + 1 !== numSetBonuses)
                setBonusText += "<br>"
        }
        ttSetBonuses.text = setBonusText

        ttRect.height = getTooltipHeight()
    }

    function getTooltipHeight() {
        var height = 0;
        height += getEffectiveHeight(ttTitle)
        height += getEffectiveHeight(ttBind)
        height += ttUnique.text !== "" ? getEffectiveHeight(ttUnique) : 0
        height += getEffectiveHeight(ttItemSlot)
        height += ttWeaponDamageRange.text !== "" ? getEffectiveHeight(ttWeaponDamageRange) * 2 : 0
        height += showDurabilityInTooltip === true ? getEffectiveHeight(ttDurability) : 0
        height += ttBaseStats.text !== "" ? getEffectiveHeight(ttBaseStats) : 0
        height += ttClassRestrictions.text !== "" ? getEffectiveHeight(ttClassRestrictions) : 0
        height += getEffectiveHeight(ttLevelRequirement)
        height += ttEquipEffect.text !== "" ? getEffectiveHeight(ttEquipEffect) : 0
        height += ttFlavourText.text !== "" ? getEffectiveHeight(ttFlavourText) : 0
        height += ttSetName.text !== "" ? getEffectiveHeight(ttSetName) : 0
        height += ttSetItems.text !== "" ? getEffectiveHeight(ttSetItems) : 0
        height += ttSetBonuses.text !== "" ? getEffectiveHeight(ttSetBonuses) : 0

        height += 10

        return height
    }

    function getEffectiveHeight(obj) {
        return obj.contentHeight + obj.anchors.topMargin - (obj.height < obj.contentHeight ? obj.contentHeight - obj.height : 0)
    }

    visible: false

    width: ttTitle.width > ttEquipEffect.width ? ttTitle.width + 20 :
                                                 ttEquipEffect.width +  20

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
        id: ttUnique

        anchors {
            top: ttBind.bottom
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

        height: text !== "" ? 10 : 0
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
        id: ttBaseStats

        anchors {
            top: ttWeaponDps.visible ? ttWeaponDps.bottom :
                                       ttItemSlot.bottom
            topMargin: 3
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

        height: 10

        text: "Durability 105 / 105"

        visible: ttRect.visible && showDurabilityInTooltip

        color: "white"
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: ttClassRestrictions

        anchors {
            top: ttDurability.visible ? ttDurability.bottom : ttBaseStats.visible ?
                                            ttBaseStats.bottom :
                                            ttItemType.bottom
            topMargin: 5
            left: ttRect.left
            leftMargin: 10
        }

        font {
            family: "Arial"
            pointSize: 9
        }


        height: text !== "" ? 10 : 0
        visible: ttRect.visible && text !== ""

        color: "white"
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: ttLevelRequirement

        anchors {
            top: ttClassRestrictions.visible ? ttClassRestrictions.bottom :
                                               showDurabilityInTooltip ? ttDurability.bottom :
                                                                         ttBaseStats.text !== "" ? ttBaseStats.bottom :
                                                                                                   ttItemSlot.bottom
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

    Text {
        id: ttFlavourText

        anchors {
            top: ttEquipEffect.text !== "" ? ttEquipEffect.bottom :
                                             ttLevelRequirement.bottom
            topMargin: 5
            left: ttRect.left
            leftMargin: 10
        }

        font {
            family: "Arial"
            pointSize: 9
        }

        width: Text.width < 280 ? Text.width:
                                  280

        visible: ttRect.visible && text !== ""
        wrapMode: Text.WordWrap

        color: "#ffd100"
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: ttSetName

        anchors {
            top: ttFlavourText.text !== "" ? ttFlavourText.bottom :
                                             ttEquipEffect.text !== "" ? ttEquipEffect.bottom :
                                                                         ttLevelRequirement.bottom
            topMargin: 15
            left: ttRect.left
            leftMargin: 10
        }

        font {
            family: "Arial"
            pointSize: 9
        }

        width: Text.width < 280 ? Text.width:
                                  280
        visible: ttRect.visible && text !== ""
        wrapMode: Text.WordWrap
        color: "#ffd100"
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: ttSetItems

        anchors {
            top: ttSetName.bottom
            topMargin: 5
            left: ttRect.left
            leftMargin: 10
        }

        font {
            family: "Arial"
            pointSize: 9
        }

        width: Text.width < 280 ? Text.width:
                                  280
        visible: ttRect.visible && text !== ""
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: ttSetBonuses

        anchors {
            top: ttSetItems.bottom
            topMargin: 15
            left: ttRect.left
            leftMargin: 10
        }

        font {
            family: "Arial"
            pointSize: 9
        }

        width: Text.width < 280 ? Text.width:
                                  280
        visible: ttRect.visible && text !== ""
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }
}
