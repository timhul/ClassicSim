import QtQuick 2.0

Rectangle {
    color: "transparent"

    property int sideLength: 55

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
                color: character.faction === root.alliance ? "blue" :
                                                             root.gray

                font {
                    family: root.fontText
                    pointSize: 16
                }

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            onRectangleClicked: character.selectFaction(root.alliance)
            onRectangleRightClicked: character.selectFaction(root.alliance)
        }

        RectangleBorders {
            rectColor: root.darkDarkGray
            height: sideLength
            width: sideLength

            Text {
                anchors.fill: parent

                text: "H"
                color: character.faction === root.horde ? "red" :
                                                          root.gray

                font {
                    family: root.fontText
                    pointSize: 16
                }

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            onRectangleClicked: character.selectFaction(root.horde)
            onRectangleRightClicked: character.selectFaction(root.horde)
        }
    }
}
