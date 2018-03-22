import QtQuick 2.0

Rectangle {
    id: rightNavBar

    property int choiceHeight: 70
    property string fontFamily: "Cambria Math"
    property string fontSize: "20"

    width: 150

    color: "white"

    // TODO: The choices should be made into a separate QML object in order to support clicks etc.
    Rectangle {
        id: chooseClassRect
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        height: choiceHeight

        color: "yellow"

        Text {
            anchors.fill: parent

            text: "Class"

            font {
                family: fontFamily
                pointSize: fontSize
            }

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        MouseArea {
            anchors.fill: parent

            onClicked: console.log("Clicked class choice")
        }
    }

    // TODO: The choices should be made into a separate QML object in order to support clicks etc.
    Rectangle {
        id: chooseTalentsRect
        anchors {
            top: chooseClassRect.bottom
            left: parent.left
            right: parent.right
        }

        height: choiceHeight

        color: "blue"

        Text {
            anchors.fill: parent

            text: "Talents"

            font {
                family: fontFamily
                pointSize: fontSize
            }

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        MouseArea {
            anchors.fill: parent

            onClicked: console.log("Clicked talent choice")
        }
    }

    // TODO: The choices should be made into a separate QML object in order to support clicks etc.
    Rectangle {
        id: chooseBuffsRect
        anchors {
            top: chooseTalentsRect.bottom
            left: parent.left
            right: parent.right
        }

        height: choiceHeight

        color: "green"

        Text {
            anchors.fill: parent

            text: "Buffs"

            font {
                family: fontFamily
                pointSize: fontSize
            }

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        MouseArea {
            anchors.fill: parent

            onClicked: console.log("Clicked buff choice")
        }
    }

    // TODO: The choices should be made into a separate QML object in order to support clicks etc.
    Rectangle {
        id: chooseFullSimSettingsRect
        anchors {
            top: chooseBuffsRect.bottom
            left: parent.left
            right: parent.right
        }

        height: choiceHeight

        color: "red"

        Text {
            anchors.fill: parent

            text: "Settings"

            font {
                family: fontFamily
                pointSize: fontSize
            }

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        MouseArea {
            anchors.fill: parent

            onClicked: console.log("Clicked full sim settings choice")
        }
    }
}
