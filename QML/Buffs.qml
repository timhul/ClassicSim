import QtQuick 2.0

Rectangle {
    color: "transparent"

    anchors.fill: parent

    GridView {
        anchors.fill: parent
        anchors.margins: 20

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
}
