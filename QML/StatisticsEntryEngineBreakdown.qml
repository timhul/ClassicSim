import QtQuick 2.0

Rectangle {
    width: 600
    height: 30

    color: "transparent"

    property string event
    property string percentage
    property int total
    property string permin

    Row {
        anchors.fill: parent

        property int attemptsWidth: 120
        property int percentageWidth: 120

        RectangleBorders {
            height: parent.height
            width: 200

            TextSmall {
                text: event
                anchors.leftMargin: 10

                horizontalAlignment: Text.AlignLeft
                wrapMode: Text.WordWrap
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            TextSmall {
                text: percentage
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            TextSmall {
                text: total
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            TextSmall {
                text: permin
            }
        }
    }
}
