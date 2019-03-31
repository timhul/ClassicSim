import QtQuick 2.0

RectangleBorders {
    height: 20
    width: parent.width

    property int sortBoxHeight: 18
    property int sortBoxWidth: parent.width / 3 - 1

    state: settings.displayStatsType

    Row {
        height: parent.height
        width: parent.width - 3
        anchors {
            right: parent.right
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: sortBoxWidth

            onRectangleClicked: settings.selectDisplayStat("MELEE")
            onRectangleRightClicked: settings.selectDisplayStat("MELEE")

            rectColor: settings.displayStatsType === "MELEE" ? root.darkGray :
                                                               root.darkDarkGray

            Text {
                text: "Melee"

                font {
                    family: "Arial"
                    pointSize: 9
                }

                anchors.fill: parent

                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: sortBoxWidth

            onRectangleClicked: settings.selectDisplayStat("RANGED")
            onRectangleRightClicked: settings.selectDisplayStat("RANGED")

            rectColor: settings.displayStatsType === "RANGED" ? root.darkGray :
                                                                root.darkDarkGray

            Text {
                text: "Ranged"

                font {
                    family: "Arial"
                    pointSize: 9
                }

                anchors.fill: parent

                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: sortBoxWidth

            onRectangleClicked: settings.selectDisplayStat("SPELL")
            onRectangleRightClicked: settings.selectDisplayStat("SPELL")

            rectColor: settings.displayStatsType === "SPELL" ? root.darkGray :
                                                               root.darkDarkGray

            Text {
                text: "Spell"

                font {
                    family: "Arial"
                    pointSize: 9
                }

                anchors.fill: parent

                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}

