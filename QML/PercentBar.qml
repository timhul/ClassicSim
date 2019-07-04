import QtQuick 2.0

RectangleBorders {
    property color fillColor
    property color backgroundColor
    property string barText
    property string barTextLeft: ""
    property string barTextRight: ""
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

        color: parent.percent > 75 ? "black" : "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        font {
            family: "Arial"
            pointSize: 12
        }

        anchors.fill: parent
        anchors.leftMargin: 10

        text: barTextLeft

        color: parent.percent > 25 ? "black" : "white"
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        font {
            family: "Arial"
            pointSize: 12
        }

        anchors.fill: parent
        anchors.rightMargin: 10

        text: barTextRight

        color: parent.percent > 95 ? "black" : "white"
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
    }
}
