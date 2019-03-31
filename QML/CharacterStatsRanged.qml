import QtQuick 2.0

Column {
    property string fontFamily: root.fontText

    anchors {
        fill: parent
        leftMargin: 10
        topMargin: 2
    }

    Text {
        height: 15

        text: "Strength: " + character.strength
        color: "white"

        font {
            family: fontFamily
            pointSize: 10
        }

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Text {
        height: 15

        text: "Agility: " + character.agility
        color: "white"

        font {
            family: fontFamily
            pointSize: 10
        }

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Text {
        height: 15

        text: "Stamina: " + character.stamina
        color: "white"

        font {
            family: fontFamily
            pointSize: 10
        }

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Text {
        height: 15

        text: "Intellect: " + character.intellect
        color: "white"

        font {
            family: fontFamily
            pointSize: 10
        }

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Text {
        height: 15

        text: "Spirit: " + character.spirit
        color: "white"

        font {
            family: fontFamily
            pointSize: 10
        }

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Text {
        height: 15
        property string crit: character.rangedCritChance.length < 8 ? "Critical strike: " :
                                                                "Crit: "

        text: crit + character.rangedCritChance + "%"
        color: "white"

        font {
            family: fontFamily
            pointSize: 10
        }

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Text {
        height: 15

        text: "Ranged Hit: " + character.rangedHitChance + "%"
        color: "white"

        font {
            family: fontFamily
            pointSize: 10
        }

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Text {
        height: 15

        text: "Ranged AP: " + character.rangedAttackPower
        color: "white"

        font {
            family: fontFamily
            pointSize: 10
        }

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Text {
        height: 15

        text: "Ranged skill: " + character.wpnSkillRanged
        color: "white"

        font {
            family: fontFamily
            pointSize: 10
        }

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
}
