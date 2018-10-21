import QtQuick 2.0

Rectangle {
    color: "transparent"
    height: 45
    width: parent.width
    property string title

    Text {
        text: title

        font {
            family: "Arial"
            pointSize: 12
        }

        anchors.fill: parent

        color: "white"
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignBottom
    }
}
