import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

Window {
    id: root
    visible: true
    width: 1500
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

    function qualityColor(quality) {
        switch (quality) {
        case "POOR":
            return qualityPoor
        case "COMMON":
            return qualityCommon
        case "UNCOMMON":
            return qualityUncommon
        case "RARE":
            return qualityRare
        case "EPIC":
            return qualityEpic
        case "LEGENDARY":
            return qualityLegendary
        default:
            return "red"
        }
    }

    function createNewObject(parentObject, qmlFile) {
        var object = Qt.createComponent(qmlFile).createObject(parentObject)
        return object
    }

    Connections {
        target: character
        onQuickSimChanged: {
            continuousDpsUpdateText.text = value;
            percentualDifference.text = change;
            percentualDifference.color = positive ? brightGreen : brightRed
        }
    }

    FactionChoice {
        id: factionChoice

        anchors {
            left: parent.left
            leftMargin: 5
            top: parent.top
            topMargin: 5
        }
    }

    ClassChoice {
        id: classChoice

        anchors {
            left: factionChoice.right
            leftMargin: 5
            top: parent.top
            topMargin: 5
        }
    }

    RaceChoice {
        id: raceChoice

        anchors {
            left: classChoice.right
            leftMargin: 5
            top: parent.top
            topMargin: 5
        }
    }

    ComboBox {
        id: patchChoice
        anchors {
            right: continuousDpsUpdateRect.left
            rightMargin: 20
            bottom: mainView.top
        }

        width: 200
        model: [
            "1.0.0 (Beta)",
            "1.1.0 (US Release)",
            "1.2.0 (Maraudon)",
            "1.3.0 (Dire Maul)",
            "1.4.0 (Benediction/Rhok'delar)",
            "1.5.0 (Battlegrounds)",
            "1.6.0 (Blackwing Lair)",
            "1.7.0 (Zul'Gurub)",
            "1.8.0 (Dragon World Bosses)",
            "1.9.0 (Ahn'Qiraj)",
            "1.10.0 (Tier 0.5)",
            "1.11.0 (Naxxramas)",
            "1.12.1"]

        currentIndex: 12

        onActivated: settings.setPatch(currentText)
    }

    ComboBox {
        id: creatureType
        anchors {
            bottom: patchChoice.top
            bottomMargin: 2
            right: continuousDpsUpdateRect.left
            rightMargin: 20
        }

        width: 200
        model: [
            "Beast",
            "Demon",
            "Dragonkin",
            "Elemental",
            "Giant",
            "Humanoid",
            "Mechanical",
            "Undead"
        ]

        currentIndex: 0

        onActivated: settings.setCreatureType(currentText)
    }

    ComboBox {
        id: ruleset
        anchors {
            bottom: creatureType.top
            bottomMargin: 2
            right: continuousDpsUpdateRect.left
            rightMargin: 20
        }

        width: 200
        model: [
            "Standard",
            "Vaelastrasz",
            "Loatheb"
        ]

        currentIndex: 0

        onActivated: settings.selectRuleset(currentIndex)
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

        Text {
            font {
                family: "Arial"
                pointSize: 9
            }

            text: settings.simProgressString

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            anchors.left: parent.left
            anchors.leftMargin: 5

            color: "gray"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
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

        state: "EQUIPMENT"

        onTalentsClicked: state = "TALENTS"
        onEquipmentClicked: state = "EQUIPMENT"
        onBuffsClicked: state = "BUFFS"
        onRotationClicked: state = "ROTATION"
        onSettingsClicked: state = "SETTINGS"
        onStatisticsClicked: state = "STATISTICS"
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
            x: parent.width / 2 - width / 2
            y: parent.height / 2 - height / 2
        }

        Equipment {
            visible: parent.state === "EQUIPMENT"
        }

        Buffs {
            visible: parent.state === "BUFFS"
        }

        Rotations {
            visible: parent.state === "ROTATION"
            x: parent.width / 2 - width / 2
            y: parent.height / 2 - height / 2
        }

        Statistics {
            visible: parent.state === "STATISTICS"
        }

        Settings {
            visible: parent.state ===  "SETTINGS"
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

    Text {
        text: "All art assets ©Blizzard Entertainment (2018)."
        height: 15
        anchors {
            left: parent.left
            bottom: parent.bottom
            right:parent.right
        }

        font {
            family: "Arial"
            pointSize: 9
        }

        color: "black"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignBottom
    }
}
