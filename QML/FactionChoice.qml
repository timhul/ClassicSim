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

            TextSmall {
                pointSize: 16

                text: "A"
                color: character.isAlliance ? "blue" :
                                              root.gray
            }

            onRectangleClicked: character.selectFaction(Faction.Alliance)
            onRectangleRightClicked: character.selectFaction(Faction.Alliance)
        }

        RectangleBorders {
            rectColor: root.darkDarkGray
            height: sideLength
            width: sideLength

            TextSmall {
                pointSize: 16

                text: "H"
                color: character.isHorde ? "red" :
                                           root.gray
            }

            onRectangleClicked: character.selectFaction(Faction.Horde)
            onRectangleRightClicked: character.selectFaction(Faction.Horde)
        }
    }
}
