import QtQuick 2.0

Rectangle {
    width: 600
    height: 30

    color: "transparent"

    property url iconurl
    property string name
    property string avguptime
    property string minuptime
    property string maxuptime

    Row {
        anchors.fill: parent

        property int attemptsWidth: 120
        property int percentageWidth: 120

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
            width: 200

            TextSmall {
                text: name
                anchors.leftMargin: 10

                horizontalAlignment: Text.AlignLeft
                wrapMode: Text.WordWrap
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            TextSmall {
                text: avguptime
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.attemptsWidth

            TextSmall {
                text: minuptime
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.attemptsWidth

            TextSmall {
                text: maxuptime
            }
        }
    }
}
