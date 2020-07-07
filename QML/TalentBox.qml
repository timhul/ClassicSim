import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    property string treePos
    property string talentPos
    property color talentAvailable: "#00ff16"
    property color talentMaxed: root.gold

    color: "transparent"

    width: parent.width
    height: parent.height

    Connections {
        target: talents
        function onTalentsUpdated() { update() }
        function onClassChanged() { classChange() }
    }

    onVisibleChanged: {
        if (visible === true) {
            update()
        }
    }

    function classChange() {
        if (talents.showPosition(treePos, talentPos) === false) {
            icon.visible = false
            border.visible = false
            highlight.visible = false
            return
        }

        icon.visible = true
        border.visible = true
        icon.source = talents.getIcon(treePos, talentPos)
        ttTitle.text = talents.getTalentName(treePos, talentPos)

        update()
        bottomArrow.updateBottomArrow()
        rightArrow.updateRightArrow()
    }

    function update() {
        rank.text = talents.getRank(treePos, talentPos)
        rank.color = talents.isMaxed(treePos, talentPos) ? talentMaxed :
                                                           talentAvailable
        unavailable.visible = icon.visible && !talents.isAvailable(treePos, talentPos)
        bottomArrow.updateBottomArrow()
        rightArrow.updateRightArrow()
        border.color = unavailable.visible ? root.gray :
                                             talents.isMaxed(treePos, talentPos) ? talentMaxed :
                                                                                  talentAvailable
        updateTooltip()
    }

    function updateTooltip() {
        ttRank.text = "Rank " + talents.getRank(treePos, talentPos) + "/" + talents.getMaxRank(treePos, talentPos)
        ttDescription.text = talents.getCurrentRankDescription(treePos, talentPos)

        ttRequirements.visible = ttRect.visible && !talents.isAvailable(treePos, talentPos) && talents.hasTalentPointsRemaining()
        ttRequirements.text = !ttRequirements.visible ? "" : talents.getRequirements(treePos, talentPos)

        ttNextRank.visible = ttRect.visible && talents.isActive(treePos, talentPos) && !talents.isMaxed(treePos, talentPos)
        ttNextRankDescription.text = ttNextRankDescription.visible ? talents.getNextRankDescription(treePos,  talentPos) : ""

        ttRect.height = getTooltipHeight()
    }

    function getTooltipHeight() {
        var height = 0
        height += ttTitle.height + ttTitle.anchors.topMargin
        height += ttRank.height + ttRank.anchors.topMargin
        height += ttRequirements.visible ?  ttRequirements.height + ttRequirements.anchors.topMargin : 0
        height += ttDescription.height + ttDescription.anchors.topMargin
        height += ttNextRank.visible ? ttNextRank.height + ttNextRank.anchors.topMargin : 0
        height += ttNextRankDescription.visible ? ttNextRankDescription.height + ttNextRankDescription.anchors.topMargin : 0
        height += 10 // bottom margin
        return height
    }

    function getArrowIcon(arrowIdentifier) {
        switch (arrowIdentifier) {
        case "VERTICAL0":
            return "Assets/talents/arrow-vertical-0.png"
        case "VERTICAL1":
            return "Assets/talents/arrow-vertical-1.png"
        case "VERTICAL2":
            return "Assets/talents/arrow-vertical-2.png"
        case "RIGHT":
            return "Assets/talents/arrow-horizontal-0.png"
        case "HOOK":
            return "Assets/talents/arrow-hook.png"
        default:
            return ""
        }
    }

    Rectangle {
        id: border
        width: parent.width * 0.8
        height: width
        radius: 4

        x: parent.width / 2 - width / 2
        y: parent.height / 2 - height / 2

        visible: talents.showPosition(treePos, talentPos)

        color: unavailable.visible ? root.gray :
                                     talents.isMaxed(treePos, talentPos) ? talentMaxed :
                                                                           talentAvailable

        Image {
            id: icon
            source: talents.getIcon(treePos, talentPos)

            anchors.fill: parent
            anchors.margins: 1
        }

        InnerShadow {
            id: highlight
            anchors.fill: icon
            radius: 8.0
            samples: 16
            horizontalOffset: -3
            verticalOffset: 3
            color: root.gray
            source: icon
            visible: false
        }

        Colorize {
            id: unavailable
            visible: icon.visible && !talents.isAvailable(treePos, talentPos)
            anchors.fill: icon
            source: icon
            hue: 0.0
            saturation: 0.0
            lightness: 0.0
        }
    }


    RectangleBorders {
        visible: icon.visible && !unavailable.visible
        height: 18
        width: 18
        rectColor: root.darkDarkGray

        anchors {
            right: parent.right
            bottom: parent.bottom
        }

        Text {
            id: rank
            text: talents.getRank(treePos, talentPos)

            anchors.fill: parent

            font {
                family: "Arial Narrow"
                pointSize: 10
            }

            color: talents.isMaxed(treePos, talentPos) ? talentMaxed :
                                                         talentAvailable

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: {
            if (mouse.button === Qt.RightButton) {
                if (mouse.modifiers & Qt.ShiftModifier)
                    talents.minRank(treePos, talentPos)
                else
                    talents.decrementRank(treePos, talentPos)
            }
            else {
                if (mouse.modifiers & Qt.ShiftModifier)
                    talents.maxRank(treePos, talentPos)
                else
                    talents.incrementRank(treePos, talentPos)
            }
        }

        onPressAndHold: {
            if (mouse.button === Qt.RightButton)
                talents.minRank(treePos, talentPos)
            else
                talents.maxRank(treePos, talentPos)
        }

        onEntered: {
            highlight.visible = icon.visible
            updateTooltip()
        }
        onExited: {
            highlight.visible = false
            updateTooltip()
        }
    }

    RectangleBorders {
        id: ttRect
        anchors {
            left: parent.right
            bottom: parent.top
        }

        width: parent.width * 4
        height: getTooltipHeight()

        rectColor: root.darkDarkGray
        opacity: 0.8
        setRadius: 4

        visible: highlight.visible
    }

    Text {
        id: ttTitle
        text: talents.getTalentName(treePos, talentPos)

        visible: ttRect.visible

        anchors {
            top: ttRect.top
            left: ttRect.left
            topMargin: 10
            leftMargin: 10
        }
        height : 20
        font {
            family: "Arial"
            pointSize: 10
        }

        color: "white"

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: ttRank
        text: "Rank " + talents.getRank(treePos, talentPos) + "/" + talents.getMaxRank(treePos, talentPos)

        visible: ttRect.visible

        anchors {
            top: ttTitle.bottom
            left: ttRect.left
            topMargin: 3
            leftMargin: 10
        }
        height : 10
        font {
            family: "Arial"
            pointSize: 8
        }

        color: "white"

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: ttRequirements
        text: !ttRequirements.visible ? "" : talents.getRequirements(treePos, talentPos)

        visible: ttRect.visible && !talents.isAvailable(treePos, talentPos) && talents.hasTalentPointsRemaining()

        anchors {
            top: ttRank.bottom
            left: ttRect.left
            topMargin: 5
            leftMargin: 10
        }

        width: ttRect.width - 20

        font {
            family: "Arial"
            pointSize: 8
        }

        color: "red"
        wrapMode: Text.WordWrap

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: ttDescription
        text: talents.getCurrentRankDescription(treePos, talentPos)

        visible: ttRect.visible

        anchors {
            top: ttRequirements.visible ? ttRequirements.bottom : ttRank.bottom
            left: ttRect.left
            topMargin: 3
            leftMargin: 10
        }

        width: ttRect.width - 20

        font {
            family: "Arial"
            pointSize: 8
        }

        color: root.gold
        wrapMode: Text.WordWrap

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: ttNextRank
        text: "Next rank:"

        visible: ttRect.visible && talents.isActive(treePos, talentPos) && !talents.isMaxed(treePos, talentPos)

        anchors {
            top: ttDescription.bottom
            left: ttRect.left
            topMargin: 15
            leftMargin: 10
        }

        font {
            family: "Arial"
            pointSize: 8
        }

        color: "white"

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: ttNextRankDescription
        text: talents.getNextRankDescription(treePos,  talentPos)

        visible: ttNextRank.visible

        anchors {
            top: ttNextRank.bottom
            left: ttRect.left
            topMargin: 5
            leftMargin: 10
        }

        width: ttRect.width - 20

        font {
            family: "Arial"
            pointSize: 8
        }

        color: root.gold
        wrapMode: Text.WordWrap

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    Image {
        id: bottomArrow

        function updateBottomArrow() {
            visible = talents.showBottomArrow(treePos, talentPos)
            bottomArrowDark.visible = visible && (!talents.bottomChildAvailable(treePos, talentPos) || (!talents.hasTalentPointsRemaining() && !talents.bottomChildActive(treePos, talentPos)))

            if (visible === false)
                return

            bottomArrowType = talents.getBottomArrow(treePos, talentPos)
            source = getArrowIcon(bottomArrowType)
        }

        property string bottomArrowType: talents.getBottomArrow(treePos, talentPos)
        source: getArrowIcon(bottomArrowType)
        height: {
            switch (bottomArrowType) {
            case "VERTICAL0":
                return parent.height * 0.2
            case "VERTICAL1":
                return parent.height * 1.20
            case "VERTICAL2":
                return parent.height * 2.4
            }
        }

        visible: talents.showBottomArrow(treePos, talentPos)

        anchors {
            top: border.bottom
        }
        x: parent.width / 2 - width / 2
    }

    Colorize {
        id: bottomArrowDark
        visible: bottomArrow.visible && (!talents.bottomChildAvailable(treePos, talentPos) || (!talents.hasTalentPointsRemaining() && !talents.bottomChildActive(treePos, talentPos)))
        anchors.fill: bottomArrow
        source: bottomArrow
        hue: 0.0
        saturation: 0.0
        lightness: 0.0
    }

    Image {
        id: rightArrow

        function updateRightArrow() {
            visible = talents.showRightArrow(treePos, talentPos)
            rightArrowDark.visible = visible && (!talents.rightChildAvailable(treePos, talentPos) || (!talents.hasTalentPointsRemaining() && !talents.rightChildActive(treePos, talentPos)))

            if (visible === false)
                return

            rightArrowType = talents.getRightArrow(treePos, talentPos)
            source = getArrowIcon(rightArrowType)
        }

        property string rightArrowType: talents.getRightArrow(treePos, talentPos)
        source: getArrowIcon(rightArrowType)
        height: {
            switch (rightArrowType) {
            case "HOOK":
                return parent.height * 0.73
            case "RIGHT":
                return parent.height * 0.2
            }
        }
        width: height

        visible: talents.showRightArrow(treePos, talentPos)

        anchors {
            left: border.right
        }

        y: {
            switch (rightArrowType) {
            case "HOOK":
                return height / 2
            case "RIGHT":
                return parent.height / 2 - 5
            }

            return 0
        }
    }

    Colorize {
        id: rightArrowDark
        visible: rightArrow.visible && (!talents.rightChildAvailable(treePos, talentPos) || (!talents.hasTalentPointsRemaining() && !talents.rightChildActive(treePos, talentPos)))
        anchors.fill: rightArrow
        source: rightArrow
        hue: 0.0
        saturation: 0.0
        lightness: 0.0
    }
}
