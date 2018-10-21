import QtQuick 2.0

Rectangle {
    width: 600
    height: 30

    color: "transparent"

    property url iconurl
    property string name
    property string totaldmgabsolute
    property string totaldmgpercentage

    Row {
        anchors.fill: parent

        RectangleBorders {
            height: parent.height
            width: height

            Image {
                height: parent.height - 6
                width: height
                x: 3
                y: 3

                source: iconurl
            }
        }

        RectangleBorders {
            height: parent.height
            width: 125

            TextSmall {
                text: name
                anchors.leftMargin: 10

                horizontalAlignment: Text.AlignLeft
            }
        }

        RectangleBorders {
            height: parent.height
            width: 120

            TextSmall {
                text: totaldmgabsolute
            }
        }

        RectangleBorders {
            height: parent.height
            width: 75

            TextSmall {
                text: totaldmgpercentage
            }
        }
    }
}
