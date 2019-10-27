import QtQuick 2.0

Rectangle {
    color: "transparent"

    anchors.fill: parent

    Row {
        anchors.fill: parent
        anchors.margins: 20

        GridView {
            interactive: false
            height: parent.height
            width: parent.width * 0.75

            cellWidth: 430
            cellHeight: 30

            model: buffModel
            delegate: BuffBox {
                buffName: name
                buffIcon: icon
                buffText: name + "\n" + description
                buffActive: _active

                onToggleSingleBuff: settings.toggleSingleBuff(name)
                onSelectRangeOfBuffs: settings.selectRangeOfBuffs(name)
                onClearBuffsAndSelectSingle: settings.clearBuffsAndSelectSingleBuff(name)
            }

            flow: GridView.FlowTopToBottom
        }

        GridView {
            interactive: false
            height: parent.height
            width: parent.width * 0.25

            cellWidth: 280
            cellHeight: 50

            model: debuffModel
            delegate: BuffBox {
                isBuff: false
                buffName: name
                buffIcon: icon
                buffText: name + "\n" + description
                buffActive: _active
                selectedColor: "#8c5c15"
                selectedHighlightColor: "#ff6600"
                width: 270
                height: 45

                onToggleSingleBuff: settings.toggleSingleDebuff(name)
                onSelectRangeOfBuffs: settings.selectRangeOfDebuffs(name)
                onClearBuffsAndSelectSingle: settings.clearDebuffsAndSelectSingleDebuff(name)
            }

            flow: GridView.FlowTopToBottom
        }
    }
}
