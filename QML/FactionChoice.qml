import QtQuick 2.0

Rectangle {
    color: "transparent"

    property int sideLength: 55
    property bool alliance: false
    property bool horde: true

    height: sideLength * 2
    width: sideLength

    Column {
        anchors.fill: parent

        RectangleBorders {
            rectColor: root.darkDarkGray
            height: sideLength
            width: sideLength

            Text {
                anchors.fill: parent

                text: "A"
                color: character.faction === alliance ? "blue" :
                                                        root.gray

                font {
                    family: root.fontText
                    pointSize: 16
                }

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            onRectangleClicked: character.selectFaction(alliance)
            onRectangleRightClicked: character.selectFaction(alliance)
        }

        RectangleBorders {
            rectColor: root.darkDarkGray
            height: sideLength
            width: sideLength

            Text {
                anchors.fill: parent

                text: "H"
                color: character.faction === horde ? "red" :
                                                     root.gray

                font {
                    family: root.fontText
                    pointSize: 16
                }

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            onRectangleClicked: character.selectFaction(horde)
            onRectangleRightClicked: character.selectFaction(horde)
        }
    }
}
