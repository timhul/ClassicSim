import QtQuick 2.0

Column {
    property string fontFamily: root.fontText

    anchors {
        fill: parent
        leftMargin: 10
        topMargin: 2
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: "Strength: " + character.strength
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: "Agility: " + character.agility
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: "Stamina: " + character.stamina
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: "Intellect: " + character.intellect
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: "Spirit: " + character.spirit
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        property string crit: character.rangedCritChance.length < 8 ? "Critical strike: " :
                                                                      "Crit: "

        text: crit + character.rangedCritChance + "%"
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: "Ranged Hit: " + character.rangedHitChance + "%"
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: "Ranged AP: " + character.rangedAttackPower
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: "Ranged skill: " + character.wpnSkillRanged
    }
}
