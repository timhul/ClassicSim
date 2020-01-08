import QtQuick 2.0

RectangleBorders {
    width: 1025
    height: 45

    signal entryClicked();

    property int itemid
    property string entryName
    property string entryQuality
    property string entrySpeed
    property string entryDps
    property string entryPhase
    property string entrySource
    property string entryType
    property string entryReq
    property string entryItemlvl
    property string entryIcon

    rectColorHighlighted: "#232323"

    onRectangleClicked: {
        console.log("Clicked", entryName)
        entryClicked();
    }

    Row {

        width: parent.width - x
        height: parent.height
        x: 3

        Image {
            id: icon

            height: 40
            width: 40

            source: "Assets/items/" + entryIcon

            y: parent.height / 2 - height / 2
        }

        Rectangle {
            color: "transparent"
            height: parent.height
            width: 5
        }

        Text {
            id: textName
            text: entryName

            width: 300
            height: parent.height

            color: root.qualityColor(entryQuality)

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

            font {
                family: root.fontText
                pointSize: 10
            }

            color: "white"

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            id: textSpeed
            text: entrySpeed

            width: 50
            height: parent.height

            font {
                family: root.fontText
                pointSize: 10
            }

            color: "white"

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            id: textPhase
            text: entryPhase

            width: 100
            height: parent.height

            font {
                family: root.fontText
                pointSize: 10
            }

            color: "white"

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            id: textType
            text: entryType

            width: 80
            height: parent.height

            font {
                family: root.fontText
                pointSize: 10
            }

            color: "white"

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            id: textSource
            text: entrySource

            width: 400
            height: parent.height
            wrapMode: Text.WordWrap

            font {
                family: root.fontText
                pointSize: 8
            }

            color: "white"

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }
}

