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
        border.color = unavailable.visible ? root.gray :
                                             warrior.isMaxed(treePos, talentPos) ? talentMaxed :
                                                                                  talentAvailable
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
                    console.log("Remove as many talent points as possible")
                else
                    warrior.decrementRank(treePos, talentPos)
            }
            else {
                if (mouse.modifiers & Qt.ShiftModifier)
                    console.log ("Add as many talent points as possible")
                else
                    warrior.incrementRank(treePos, talentPos)
            }
        }

        onPressAndHold: {
            if (mouse.button === Qt.RightButton)
                console.log("Remove as many talent points as possible")
            else
                console.log("Add as many talent points as possible")
        }

        onEntered: highlight.visible = icon.visible
        onExited: highlight.visible = false
    }
}
