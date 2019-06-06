import QtQuick 2.0

RectangleBorders {
    property color fillColor
    property color backgroundColor
    property string barText
    property int percent

    Row {
        anchors.fill: parent
        anchors.margins: 3

        Rectangle {
            id: fill
            height: parent.height
            width: parent.width * (percent / 100)
            color: fillColor
        }

        Rectangle {
            height: parent.height
            width: parent.width - fill.width
            color: backgroundColor
        }
    }

    Text {
        font {
            family: "Arial"
            pointSize: 12
        }

        anchors.fill: parent

        text: barText

        color: "black"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
