import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    signal clearItem();
    signal selectItem();

    property bool selected: false
    property string slotString
    property string iconSource: ""

    state: "MAINHAND"

    height: 46
    width: 46

    radius: 5
    color: "transparent"
    border.color: state === slotString ? root.gold : "transparent"
    border.width: 1

    Image {
        source: iconSource
        height: parent.height - 2
        width: parent.width - 2
        x: 1
        y: 1
    }

    MouseArea {
        anchors.fill: parent

        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: {
            if (mouse.button === Qt.RightButton)
                clearItem();
            else
                selectItem();
        }
    }
}
