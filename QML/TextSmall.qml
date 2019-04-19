import QtQuick 2.0

Text {
    property bool anchorParent: true
    property int pointSize: 9
    font {
        family: "Arial"
        pointSize: pointSize
    }

    anchors.fill: anchorParent ? parent : undefined

    color: "white"
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
}
