import QtQuick 2.0

Row {
    property string entryName
    property color entryQuality
    property string entrySpeed
    property string entryDps
    property string entryPatch
    property string entrySource
    property string entryType
    property string entryReq
    property string entryItemlvl

    width: parent.width - x
    height: 30
    x: 20

    Text {
        id: textName
        text: entryName

        width: 400
        height: parent.height

        color: root.qualityEpic

        font {
            family: root.fontText
            pointSize: 10
        }

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft

    }

    Text {
        id: textDps
        text: entryDps

        width: 50
        height: parent.height

        color: "white"

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
    }

    Text {
        id: textSpeed
        text: entrySpeed

        width: 50
        height: parent.height

        color: "white"

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
    }

    Text {
        id: textPatch
        text: entryPatch

        width: 50
        height: parent.height

        color: "white"

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
    }
}
