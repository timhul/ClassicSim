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
        property string crit: character.meleeCritChance.length < 8 ? "Critical strike: " :
                                                                     "Crit: "

        text: crit + character.meleeCritChance + "%"
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: "Hit: " + character.meleeHitChance + "%"
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: "Attack Power: " + character.meleeAttackPower
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: "MH Skill: " + character.wpnSkillMh
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: "OH Skill: " + character.wpnSkillOh
    }
}
