import QtQuick 2.0

Rectangle {
    property string treePos
    property string talentPos

    color: "transparent"

    width: parent.width
    height: parent.height

    Image {
        source: warrior.getIcon(treePos, talentPos)
        width: parent.width * 0.8
        height: width

        x: parent.width / 2 - width / 2
        y: parent.height / 2 - height / 2
    }

    MouseArea {
        anchors.fill: parent

        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: {
            if (mouse.button === Qt.RightButton) {
                if (mouse.modifiers & Qt.ShiftModifier)
                    console.log("Remove as many talent points as possible")
                else
                    console.log("Remove single talent point if possible")
            }
            else {
                if (mouse.modifiers & Qt.ShiftModifier)
                    console.log ("Add as many talent points as possible")
                else
                    console.log("Add single talent point if possible")
            }
        }

        onPressAndHold: {
            if (mouse.button === Qt.RightButton)
                console.log("Remove as many talent points as possible")
            else
                console.log("Add as many talent points as possible")
        }
    }
}
