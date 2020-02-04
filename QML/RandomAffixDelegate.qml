import QtQuick 2.0

Rectangle {
    id: container
    width: 300
    height: 30

    property string affixDescription

    color: "#1b1b1b"
    border.color: "#272727"
    border.width: 1

    Text {
        id: affixText
        text: affixDescription
        color: "#f1c501"
        anchors.centerIn: parent
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        preventStealing: true
        onClicked: {
            entryClicked(_id)
        }

        onEntered: {
            container.color = "#272727"
            affixText.color = "white"
        }

        onExited: {
            container.color = "#1b1b1b"
            affixText.color = "#f1c501"
        }
    }
}
