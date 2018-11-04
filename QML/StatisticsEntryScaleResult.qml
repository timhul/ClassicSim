import QtQuick 2.0

Rectangle {
    width: 600
    height: 30

    color: "transparent"

    property string name
    property string absvalue
    property string relvalue

    Row {
        anchors.fill: parent

        property int attemptsWidth: 120
        property int percentageWidth: 120

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
                text: absvalue
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            TextSmall {
                text: relvalue
            }
        }
    }
}
