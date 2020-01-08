import QtQuick 2.0

Rectangle {
    id: rightNavBar

    property int choiceHeight: 70
    property string fontFamily: root.fontText
    property int fontSize: 16

    signal talentsClicked();
    signal equipmentClicked();
    signal buffsClicked();
    signal rotationClicked();
    signal settingsClicked();
    signal statisticsClicked();
    signal raidSetupClicked()

    width: 150
    z: 10

    state: "TALENTS"
    color: "transparent"

    Column {
        anchors.fill: parent

        GradientSelectedButton {
            id: chooseTalentsRect

            gradientSelectedFrom: "#4f4f4f"
            gradientSelectedTo: "#333333"

            selected: parent.parent.state === "TALENTS"

            height: choiceHeight
            width: parent.width

            Text {
                anchors.fill: parent

                text: "Talents"
                color: root.colorFaction

                font {
                    family: fontFamily
                    pointSize: fontSize
                    bold: true
                }

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            onSelectButtonClicked: {
                if (parent.parent.state !== "TALENTS") {
                    parent.parent.state = "TALENTS"
                    talentsClicked()
                }
            }
        }

        GradientSelectedButton {
            id: chooseGearRect

            gradientSelectedFrom: "#4f4f4f"
            gradientSelectedTo: "#333333"

            selected: parent.parent.state === "EQUIPMENT"

            height: choiceHeight
            width: parent.width

            Text {
                anchors.fill: parent

                text: "Equipment"
                color: root.colorFaction

                font {
                    family: fontFamily
                    pointSize: fontSize
                    bold: true
                }

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            onSelectButtonClicked: {
                if (parent.parent.state !== "EQUIPMENT") {
                    parent.parent.state = "EQUIPMENT"
                    equipmentClicked()
                }
            }
        }

        GradientSelectedButton {
            id: chooseBuffsRect

            gradientSelectedFrom: "#4f4f4f"
            gradientSelectedTo: "#333333"

            selected: parent.parent.state === "BUFFS"

            height: choiceHeight
            width: parent.width

            Text {
                anchors.fill: parent

                text: "Buffs"
                color: root.colorFaction

                font {
                    family: fontFamily
                    pointSize: fontSize
                    bold: true
                }

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            onSelectButtonClicked: {
                if (parent.parent.state !== "BUFFS") {
                    parent.parent.state = "BUFFS"
                    buffsClicked()
                }
            }
        }

        GradientSelectedButton {
            id: rotationRect

            gradientSelectedFrom: "#4f4f4f"
            gradientSelectedTo: "#333333"

            selected: parent.parent.state === "ROTATION"

            height: choiceHeight
            width: parent.width

            Text {
                anchors.fill: parent

                text: "Rotation"
                color: root.colorFaction

                font {
                    family: fontFamily
                    pointSize: fontSize
                    bold: true
                }

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            onSelectButtonClicked: {
                if (parent.parent.state !== "ROTATION") {
                    parent.parent.state = "ROTATION"
                    rotationClicked()
                }
            }
        }

        GradientSelectedButton {
            id: raidSetupRect

            gradientSelectedFrom: "#4f4f4f"
            gradientSelectedTo: "#333333"

            selected: parent.parent.state === "RAIDSETUP"

            height: choiceHeight
            width: parent.width

            Text {
                anchors.fill: parent

                text: "Raid Setup"
                color: root.colorFaction

                font {
                    family: fontFamily
                    pointSize: fontSize
                    bold: true
                }

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            onSelectButtonClicked: {
                if (parent.parent.state !== "RAIDSETUP") {
                    parent.parent.state = "RAIDSETUP"
                    raidSetupClicked()
                }
            }
        }

        GradientSelectedButton {
            id: statisticsRect

            gradientSelectedFrom: "#4f4f4f"
            gradientSelectedTo: "#333333"

            selected: parent.parent.state === "STATISTICS"

            height: choiceHeight
            width: parent.width

            Text {
                anchors.fill: parent

                text: "Statistics"
                color: root.colorFaction

                font {
                    family: fontFamily
                    pointSize: fontSize
                    bold: true
                }

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            onSelectButtonClicked: {
                if (parent.parent.state !== "STATISTICS") {
                    parent.parent.state = "STATISTICS"
                    statisticsClicked()
                }
            }
        }

        GradientSelectedButton {
            id: chooseFullSimSettingsRect

            gradientSelectedFrom: "#4f4f4f"
            gradientSelectedTo: "#333333"

            selected: parent.parent.state === "SETTINGS"

            height: choiceHeight
            width: parent.width

            Text {
                anchors.fill: parent

                text: "Settings"
                color: root.colorFaction

                font {
                    family: fontFamily
                    pointSize: fontSize
                    bold: true
                }

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            onSelectButtonClicked: {
                if (parent.parent.state !== "SETTINGS") {
                    parent.parent.state = "SETTINGS"
                    settingsClicked()
                }
            }
        }
    }
}
