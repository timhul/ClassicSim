import QtQuick 2.0

Rectangle {
    color: "transparent"

    anchors.fill: parent

    Row {
        anchors.fill: parent
        GridView {
            interactive: false
            height: parent.height
            width: parent.width * 0.75

            cellWidth: 300
            cellHeight: 70

            model: buffModel
            delegate: BuffBox {
                buffName: name
                buffIcon: icon
                buffText: name + "\n" + description

                onBuffClicked: settings.selectBuff(name)
            }

            flow: GridView.FlowTopToBottom
        }

        GridView {
            interactive: false
            height: parent.height
            width: parent.width * 0.25

            cellWidth: 300
            cellHeight: 70

            model: debuffModel
            delegate: BuffBox {
                isBuff: false
                buffName: name
                buffIcon: icon
                buffText: name + "\n" + description
                selectedColor: "#8c5c15"
                selectedHighlightColor: "#ff6600"

                onBuffClicked: settings.selectDebuff(name)
            }

            flow: GridView.FlowTopToBottom
        }
    }
}
