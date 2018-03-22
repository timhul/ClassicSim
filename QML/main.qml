import QtQuick 2.10
import QtQuick.Window 2.10

Window {
    visible: true
    width: 1000
    height: 800
    title: qsTr("ClassicSim")

    property color darkGray: "#302f2e"
    property color darkBrown: "#3a2d1f"
    property color gold: "#ceac00"

    color: darkGray

    Rectangle {
        id: continuousDpsUpdateRect
        anchors {
            right: parent.right
            top: parent.top
        }

        width: 250
        height: 150

        color: darkBrown

        Text {
            id: continuousDpsUpdateText
            anchors.fill: parent

            text: "70.4"

            font {
                family: "Cambria Math"
                bold: true
                pointSize: 36
            }

            color: gold

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }

    NavigationBar {
        id: rightNavBar
        anchors {
            top: continuousDpsUpdateRect.bottom
            bottom: parent.bottom
            right: parent.right
        }

        choiceBackgroundColor: darkBrown
        fontColor: gold
    }
}
