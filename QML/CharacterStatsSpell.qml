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
        text: "Spell Damage: " + character.spellPower
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: "Spell Hit: " + character.spellHitChance
    }

    TextSmall {
        anchorParent: false
        pointSize: 10
        height: 15
        text: "Spell Crit: " + character.spellCritChance
    }
}
