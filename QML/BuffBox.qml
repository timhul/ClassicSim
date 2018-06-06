import QtQuick 2.0

RectangleBorders {
    property string buffName
    property string buffIcon
    property string buffText
    property bool selected: false

    signal buffClicked()

    height: 60
    width: 250

    rectColor: selected === true ? "#173117" : root.darkDarkGray
    rectColorHighlighted: selected === false ? root.darkGray : "#134f00"
    outerBorderColor: root.darkGray
    onRectangleClicked: buffClicked()
    onRectangleRightClicked: buffClicked()

    Connections {
        target: settings
        onExternalBuffsChanged: {
            selected = settings.buffActive(buffName)
        }
    }

    Row {
        id: row
        spacing: 10

        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
            right: parent.right
            leftMargin: 5
        }

        Image {
            id: icon
            height: 45
            width: height
            y: parent.height / 2 - height / 2

            source: buffIcon
        }

        Text {
            text: buffText

            font {
                family: "Arial"
                pointSize: 9
            }

            width: row.width - icon.width - 20
            height: row.height

            wrapMode: Text.WordWrap
            color: "white"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }
    }
}
