import QtQuick 2.0

Rectangle {
    id: rightNavBar

    property int choiceHeight: 70
    property color choiceBackgroundColor
    property color choiceSelectedBackgroundColor
    property string fontFamily: root.fontText
    property string fontSize: "16"
    property color fontColor

    signal talentsClicked();
    signal equipmentClicked();
    signal buffsClicked();
    signal settingsClicked();

    width: 150

    state: "TALENTS"
    color: "transparent"

    Column {
        height: chooseTalentsRect.height + chooseBuffsRect.height + chooseFullSimSettingsRect.height + chooseGearRect.height + characterStats.height
        width: parent.width

        RectangleBorders {
            id: chooseTalentsRect

            rectColor: parent.parent.state == "TALENTS" ? choiceSelectedBackgroundColor : choiceBackgroundColor

            height: choiceHeight
            width: parent.width

            Text {
                anchors.fill: parent

                text: "Talents"
                color: fontColor

                font {
                    family: fontFamily
                    pointSize: fontSize
                    bold: true
                }

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            onRectangleClicked: {
                if (parent.parent.state !== "TALENTS") {
                    parent.parent.state = "TALENTS"
                    talentsClicked()
                }
            }
        }

        RectangleBorders {
            id: chooseGearRect

            rectColor: parent.parent.state == "EQUIPMENT" ? choiceSelectedBackgroundColor : choiceBackgroundColor

            height: choiceHeight
            width: parent.width

            Text {
                anchors.fill: parent

                text: "Equipment"
                color: fontColor

                font {
                    family: fontFamily
                    pointSize: fontSize
                    bold: true
                }

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            onRectangleClicked: {
                if (parent.parent.state !== "EQUIPMENT") {
                    parent.parent.state = "EQUIPMENT"
                    equipmentClicked()
                }
            }
        }

        RectangleBorders {
            id: chooseBuffsRect

            rectColor: parent.parent.state == "BUFFS" ? choiceSelectedBackgroundColor : choiceBackgroundColor

            height: choiceHeight
            width: parent.width

            Text {
                anchors.fill: parent

                text: "Buffs"
                color: fontColor

                font {
                    family: fontFamily
                    pointSize: fontSize
                    bold: true
                }

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            onRectangleClicked: {
                if (parent.parent.state !== "BUFFS") {
                    parent.parent.state = "BUFFS"
                    buffsClicked()
                }
            }
        }

        RectangleBorders {
            id: chooseFullSimSettingsRect

            rectColor: parent.parent.state == "SETTINGS" ? choiceSelectedBackgroundColor : choiceBackgroundColor

            height: choiceHeight
            width: parent.width

            Text {
                anchors.fill: parent

                text: "Settings"
                color: fontColor

                font {
                    family: fontFamily
                    pointSize: fontSize
                    bold: true
                }

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            onRectangleClicked: {
                if (parent.parent.state !== "SETTINGS") {
                    parent.parent.state = "SETTINGS"
                    settingsClicked()
                }
            }
        }

        CharacterStats {
            id: characterStats
        }
    }
}
