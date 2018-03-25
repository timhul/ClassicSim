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
        target: warrior
        onTalentsUpdated: update()
    }

    function update() {
        rank.text = warrior.getRank(treePos, talentPos)
        rank.color = warrior.isMaxed(treePos, talentPos) ? talentMaxed :
                                                           talentAvailable
        unavailable.visible = icon.visible && !warrior.isAvailable(treePos, talentPos)
        bottomArrowDark.visible = bottomArrow.visible && (!warrior.bottomChildAvailable(treePos, talentPos) || !warrior.hasTalentPointsRemaining())
        border.color = unavailable.visible ? root.gray :
                                             warrior.isMaxed(treePos, talentPos) ? talentMaxed :
                                                                                  talentAvailable
        ttRank.text = "Rank " + warrior.getRank(treePos, talentPos) + "/" + warrior.getMaxRank(treePos, talentPos)
        ttDescription.text = warrior.getCurrentRankDescription(treePos, talentPos)

        ttRequirements.visible = ttRect.visible && !warrior.isAvailable(treePos, talentPos)
        ttRequirements.text = !ttRequirements.visible ? "" : warrior.getRequirements(treePos, talentPos)

        ttNextRank.visible = ttRect.visible && warrior.isActive(treePos, talentPos) && !warrior.isMaxed(treePos, talentPos)
        ttNextRankDescription.visible = ttRect.visible && warrior.isActive(treePos, talentPos) && !warrior.isMaxed(treePos, talentPos)
        ttNextRankDescription.text = ttNextRankDescription.visible ? warrior.getNextRankDescription(treePos,  talentPos) : ""

        ttRect.height = getTooltipHeight()
    }

    function updateVisibility() {
        ttNextRank.visible = ttRect.visible && warrior.isActive(treePos, talentPos) && !warrior.isMaxed(treePos, talentPos)
        ttNextRankDescription.visible = ttRect.visible && warrior.isActive(treePos, talentPos) && !warrior.isMaxed(treePos, talentPos)
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

    Rectangle {
        id: border
        width: parent.width * 0.8
        height: width
        radius: 4

        x: parent.width / 2 - width / 2
        y: parent.height / 2 - height / 2

        visible: warrior.showPosition(treePos, talentPos)

        color: unavailable.visible ? root.gray :
                                     warrior.isMaxed(treePos, talentPos) ? talentMaxed :
                                                                           talentAvailable

        Image {
            id: icon
            source: warrior.getIcon(treePos, talentPos)

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
            visible: icon.visible && !warrior.isAvailable(treePos, talentPos)
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
            text: warrior.getRank(treePos, talentPos)

            anchors.fill: parent

            font {
                family: "Arial Narrow"
                pointSize: 10
            }

            color: warrior.isMaxed(treePos, talentPos) ? talentMaxed :
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
                    warrior.minRank(treePos, talentPos)
                else
                    warrior.decrementRank(treePos, talentPos)
            }
            else {
                if (mouse.modifiers & Qt.ShiftModifier)
                    warrior.maxRank(treePos, talentPos)
                else
                    warrior.incrementRank(treePos, talentPos)
            }
        }

        onPressAndHold: {
            if (mouse.button === Qt.RightButton)
                warrior.minRank(treePos, talentPos)
            else
                warrior.maxRank(treePos, talentPos)
        }

        onEntered: {
            highlight.visible = icon.visible
            updateVisibility()
        }
        onExited: {
            highlight.visible = false
            updateVisibility()
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
        text: warrior.getTalentName(treePos, talentPos)

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
        text: "Rank " + warrior.getRank(treePos, talentPos) + "/" + warrior.getMaxRank(treePos, talentPos)

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
        text: !ttRequirements.visible ? "" : warrior.getRequirements(treePos, talentPos)

        visible: ttRect.visible && !warrior.isAvailable(treePos, talentPos)

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
        text: warrior.getCurrentRankDescription(treePos, talentPos)

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

        visible: ttRect.visible && warrior.isActive(treePos, talentPos) && !warrior.isMaxed(treePos, talentPos)

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
        text: warrior.getNextRankDescription(treePos,  talentPos)

        visible: ttRect.visible && warrior.isActive(treePos, talentPos) && !warrior.isMaxed(treePos, talentPos)

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
        source: "Assets/talents/arrow-vertical-1.png"
        height: parent.height * 1.20

        visible: warrior.showBottomArrow(treePos, talentPos)

        anchors {
            top: border.bottom
        }
        x: parent.width / 2 - width / 2
    }

    Colorize {
        id: bottomArrowDark
        visible: bottomArrow.visible && (!warrior.bottomChildAvailable(treePos, talentPos) || !warrior.hasTalentPointsRemaining())
        anchors.fill: bottomArrow
        source: bottomArrow
        hue: 0.0
        saturation: 0.0
        lightness: 0.0
    }
}
