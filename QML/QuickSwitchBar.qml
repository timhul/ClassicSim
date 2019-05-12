import QtQuick 2.0

Rectangle {
    color: "transparent"

    Row {
        width: parent.width
        height: parent.height

        Column {
            width: 150
            height: parent.height

            state: "TALENT1"

            QuickSwitchBox {
                choiceState: "TALENT1"
                choiceText: "Talent 1"

                onChoiceClicked: talents.setTalentSetup(0)
            }

            QuickSwitchBox {
                choiceState: "TALENT2"
                choiceText: "Talent 2"

                onChoiceClicked: talents.setTalentSetup(1)
            }

            QuickSwitchBox {
                choiceState: "TALENT3"
                choiceText: "Talent 3"

                onChoiceClicked: talents.setTalentSetup(2)
            }
        }

        Column {
            width: 150
            height: parent.height

            state: "EQUIPMENT1"

            QuickSwitchBox {
                choiceState: "EQUIPMENT1"
                choiceText: "Gear 1"

                onChoiceClicked: talents.setEquipmentSetup(0)
            }

            QuickSwitchBox {
                choiceState: "EQUIPMENT2"
                choiceText: "Gear 2"

                onChoiceClicked: talents.setEquipmentSetup(1)
            }

            QuickSwitchBox {
                choiceState: "EQUIPMENT3"
                choiceText: "Gear 3"

                onChoiceClicked: talents.setEquipmentSetup(2)
            }
        }

        Column {
            width: 150
            height: parent.height

            state: "BUFFS1"

            QuickSwitchBox {
                choiceState: "BUFFS1"
                choiceText: "Buff 1"

                onChoiceClicked: talents.setBuffSetup(0)
            }

            QuickSwitchBox {
                choiceState: "BUFFS2"
                choiceText: "Buff 2"

                onChoiceClicked: talents.setBuffSetup(1)
            }

            QuickSwitchBox {
                choiceState: "BUFFS3"
                choiceText: "Buff 3"

                onChoiceClicked: talents.setBuffSetup(2)
            }
        }
    }
}
