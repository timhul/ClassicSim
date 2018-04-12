import QtQuick 2.10
import QtQuick.Window 2.10

Window {
    id: root
    visible: true
    width: 1000
    height: 800
    title: qsTr("ClassicSim")

    property color darkGray: "#302f2e"
    property color darkBrown: "#3a2d1f"
    property color gold: "#ceac00"
    property color darkDarkGray: "#070707"
    property color gray: "#727171"
    property color brightGreen: "#6cf92f"
    property color brightRed: "#fc2323"
    property color qualityPoor: "#9d9d9d"
    property color qualityCommon: "#ffffff"
    property color qualityUncommon: "#1eff00"
    property color qualityRare: "#0070dd"
    property color qualityLegendary: "#ff8000"
    property color qualityEpic: "#a335ee"

    property color colorDruid: "#FF7D0A"
    property color colorHunter: "#ABD473"
    property color colorMage: "#69CCF0"
    property color colorPaladin: "#F58CBA"
    property color colorPriest: "#FFFFFF"
    property color colorRogue: "#FFF569"
    property color colorShaman: "#0070DE"
    property color colorWarlock: "#9482C9"
    property color colorWarrior: "#C79C6E"
    property string fontNumbers: "Cambria Math"
    property string fontText: "Arial"


    color: darkGray

    Connections {
        target: character
        onQuickSimChanged: {
            continuousDpsUpdateText.text = value;
            percentualDifference.text = change;
            percentualDifference.color = positive ? brightGreen : brightRed
        }
    }

    RectangleBorders {
        id: continuousDpsUpdateRect
        anchors {
            right: parent.right
            top: parent.top
        }

        width: 220
        height: 120

        rectColor: darkDarkGray

        onRectangleClicked: character.runQuickSim()

        Text {
            id: continuousDpsUpdateText
            anchors.fill: parent

            text: "0.0"

            font {
                family: fontNumbers
                bold: true
                pointSize: 36
            }

            color: gold

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }


        Text {
            id: percentualDifference
            anchors {
                bottom: parent.bottom
                bottomMargin: - 10
            }

            width: parent.width

            text: "+0.0%"

            font {
                family: fontNumbers
                bold: true
                pointSize: 10
            }

            color: gray
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

        choiceBackgroundColor: darkGray
        choiceSelectedBackgroundColor: darkDarkGray
        fontColor: gold

        state: "EQUIPMENT"//"TALENTS"

        onTalentsClicked: state = "TALENTS"
        onEquipmentClicked: state = "EQUIPMENT"
        onBuffsClicked: state = "BUFFS"
        onSettingsClicked: state = "SETTINGS"
    }

    Rectangle {
        id: mainView

        state: rightNavBar.state

        anchors {
            right: rightNavBar.left
            top: continuousDpsUpdateRect.bottom
            left: parent.left
            bottom: quickSwitchBar.top
        }

        color: darkDarkGray

        TalentCalculator {
            visible: parent.state === "TALENTS"
            width: parent.width * 0.90
            x: parent.width / 2 - width / 2
            y: 20
        }

        Equipment {
            visible: parent.state === "EQUIPMENT"
        }


    }

    QuickSwitchBar {
        id: quickSwitchBar

        anchors {
            left: parent.left
            right: rightNavBar.left
            bottom: parent.bottom
        }

        height: 125
    }
}
