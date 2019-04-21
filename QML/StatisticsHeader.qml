import QtQuick 2.0

Rectangle {
    color: "transparent"
    height: 45
    width: parent.width
    property string title

    TextSmall {
        text: title
        pointSize: 12

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignBottom
    }
}
