import QtQuick 2.0

Rectangle {
    id: rightNavBar

    property int choiceHeight: 70
    property color choiceBackgroundColor
    property color choiceSelectedBackgroundColor
    property string fontFamily: "Cambria Math"
    property string fontSize: "16"
    property color fontColor

    width: 150

    state: "TALENTS"
    color: "transparent"

    RectangleBorders {
        id: chooseTalentsRect
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        rectColor: parent.state == "TALENTS" ? choiceSelectedBackgroundColor : choiceBackgroundColor

        height: choiceHeight

        Text {
            anchors.fill: parent

            text: "Talents"
            color: fontColor

            font {
                family: fontFamily
                pointSize: fontSize
            }

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        onRectangleClicked: parent.state = "TALENTS"
    }


    RectangleBorders {
        id: chooseGearRect
        anchors {
            top: chooseTalentsRect.bottom
            left: parent.left
            right: parent.right
        }

        rectColor: parent.state == "EQUIPMENT" ? choiceSelectedBackgroundColor : choiceBackgroundColor

        height: choiceHeight

        Text {
            anchors.fill: parent

            text: "Equipment"
            color: fontColor

            font {
                family: fontFamily
                pointSize: fontSize
            }

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        onRectangleClicked: parent.state = "EQUIPMENT"
    }

    RectangleBorders {
        id: chooseBuffsRect
        anchors {
            top: chooseGearRect.bottom
            left: parent.left
            right: parent.right
        }

        rectColor: parent.state == "BUFFS" ? choiceSelectedBackgroundColor : choiceBackgroundColor

        height: choiceHeight

        Text {
            anchors.fill: parent

            text: "Buffs"
            color: fontColor

            font {
                family: fontFamily
                pointSize: fontSize
            }

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        onRectangleClicked: parent.state = "BUFFS"
    }

    RectangleBorders {
        id: chooseFullSimSettingsRect
        anchors {
            top: chooseBuffsRect.bottom
            left: parent.left
            right: parent.right
        }

        rectColor: parent.state == "SETTINGS" ? choiceSelectedBackgroundColor : choiceBackgroundColor

        height: choiceHeight

        Text {
            anchors.fill: parent

            text: "Settings"
            color: fontColor

            font {
                family: fontFamily
                pointSize: fontSize
            }

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        onRectangleClicked: parent.state = "SETTINGS"
    }

    states: [
        State {
            name: "TALENTS"
        },
        State {
            name: "EQUIPMENT"
        },
        State {
            name: "BUFFS"
        },
        State {
            name: "SETTINGS"
        }]
}
