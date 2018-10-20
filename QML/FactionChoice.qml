import QtQuick 2.0
import Faction 1.0

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
                color: character.isAlliance ? "blue" :
                                              root.gray

                font {
                    family: root.fontText
                    pointSize: 16
                }

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            onRectangleClicked: character.selectFaction(Faction.Alliance)
            onRectangleRightClicked: character.selectFaction(Faction.Alliance)
        }

        RectangleBorders {
            rectColor: root.darkDarkGray
            height: sideLength
            width: sideLength

            Text {
                anchors.fill: parent

                text: "H"
                color: character.isHorde ? "red" :
                                           root.gray

                font {
                    family: root.fontText
                    pointSize: 16
                }

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            onRectangleClicked: character.selectFaction(Faction.Horde)
            onRectangleRightClicked: character.selectFaction(Faction.Horde)
        }
    }
}
