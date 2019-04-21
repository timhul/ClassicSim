import QtQuick 2.0

Rectangle {
    width: 600
    height: 30

    color: "transparent"

    property string executor
    property string spellstatus
    property int value

    Row {
        anchors.fill: parent

        RectangleBorders {
            height: parent.height
            width: 200

            TextSmall {
                text: executor
                anchors.leftMargin: 10

                horizontalAlignment: Text.AlignLeft
                wrapMode: Text.WordWrap
            }
        }

        RectangleBorders {
            height: parent.height
            width: 200

            TextSmall {
                anchors.leftMargin: 10
                text: spellstatus
                horizontalAlignment: Text.AlignLeft
            }
        }

        RectangleBorders {
            height: parent.height
            width: 120

            TextSmall {
                text: value
            }
        }
    }
}
