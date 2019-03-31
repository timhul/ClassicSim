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
        property string crit: character.meleeCritChance.length < 8 ? "Critical strike: " :
                                                                "Crit: "

        text: crit + character.meleeCritChance + "%"
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

        text: "Hit: " + character.meleeHitChance + "%"
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

        text: "Attack Power: " + character.meleeAttackPower
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

        text: "MH Skill: " + character.wpnSkillMh
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

        text: "OH Skill: " + character.wpnSkillOh
        color: "white"

        font {
            family: fontFamily
            pointSize: 10
        }

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
}
