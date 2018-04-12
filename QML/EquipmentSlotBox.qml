import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    signal clearItem();
    signal selectItem();

    property bool selected: false
    property string slotString

    state: "MAINHAND"

    height: 46
    width: 46

    radius: 5
    color: "transparent"
    border.color: state === slotString ? root.gold : "transparent"
    border.width: 1

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
