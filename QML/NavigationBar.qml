import QtQuick 2.0

Rectangle {
    id: rightNavBar

    property int choiceHeight: 70
    property color choiceBackgroundColor
    property string fontFamily: "Cambria Math"
    property string fontSize: "16"
    property color fontColor

    width: 150

    color: "white"

    RectangleBorders {
        id: chooseTalentsRect
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        rectColor: choiceBackgroundColor

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

        onRectangleClicked: console.log("Clicked talent choice from RectangleBorders")
    }


    RectangleBorders {
        id: chooseGearRect
        anchors {
            top: chooseTalentsRect.bottom
            left: parent.left
            right: parent.right
        }

        rectColor: choiceBackgroundColor

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

        onRectangleClicked: console.log("Clicked equipment choice from RectangleBorders")
    }

    RectangleBorders {
        id: chooseBuffsRect
        anchors {
            top: chooseGearRect.bottom
            left: parent.left
            right: parent.right
        }

        rectColor: choiceBackgroundColor

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

        onRectangleClicked: console.log("Clicked buffs choice from RectangleBorders")
    }

    RectangleBorders {
        id: chooseFullSimSettingsRect
        anchors {
            top: chooseBuffsRect.bottom
            left: parent.left
            right: parent.right
        }

        rectColor: choiceBackgroundColor

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

        onRectangleClicked: console.log("Clicked settings choice from RectangleBorders")
    }
}
