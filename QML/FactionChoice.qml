import QtQuick 2.0
import Faction 1.0

Rectangle {
    color: "transparent"

    property int buttonWidth: 145
    property int buttonHeight: 55

    height: buttonHeight * 2
    width: buttonWidth

    Column {
        anchors.fill: parent

        GradientButton {
            height: buttonHeight
            width: buttonWidth

            Image {
                id: allianceImage
                height: 30
                width: 30
                source: "Assets/Alliance_64.png"

                anchors {
                    left: parent.left
                    top: parent.top
                    leftMargin: 10
                    topMargin: (parent.height - height) / 2
                }
            }

            TextSmall {
                anchorParent: false
                anchors {
                    left: allianceImage.right
                    leftMargin: 5
                    right: parent.right
                    top: parent.top
                    bottom: parent.bottom
                }

                pointSize: 16

                text: "Alliance"
                color: character.isAlliance ? "cornflowerblue" :
                                              root.gray
                horizontalAlignment: Text.AlignLeft
            }

            onButtonClicked: character.selectFaction(Faction.Alliance)
            onButtonRightClicked: character.selectFaction(Faction.Alliance)
        }

        GradientButton {
            height: buttonHeight
            width: buttonWidth

            Image {
                id: hordeImage
                height: 30
                width: 30
                source: "Assets/Horde_64.png"

                anchors {
                    left: parent.left
                    top: parent.top
                    leftMargin: 10
                    topMargin: (parent.height - height) / 2
                }
            }

            TextSmall {
                anchorParent: false
                anchors {
                    left: hordeImage.right
                    leftMargin: 5
                    right: parent.right
                    top: parent.top
                    bottom: parent.bottom
                }

                pointSize: 16

                text: "Horde"
                color: character.isHorde ? root.wineRed :
                                           root.gray
                horizontalAlignment: Text.AlignLeft
            }

            onButtonClicked: character.selectFaction(Faction.Horde)
            onButtonRightClicked: character.selectFaction(Faction.Horde)
        }
    }
}
