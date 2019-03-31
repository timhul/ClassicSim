import QtQuick 2.0

Rectangle {
    height: 175
    width: 150
    property string fontFamily: root.fontText
    color: "transparent"

    AttackModeChoice {

    }

    RectangleBorders {
        rectColor: root.darkDarkGray

        height: parent.height - 18
        width: parent.width
        anchors.bottom: parent.bottom

        CharacterStatsMelee {
            visible: settings.displayStatsType === "MELEE"
        }

        CharacterStatsRanged {
            visible: settings.displayStatsType === "RANGED"
        }
    }
}
