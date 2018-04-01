import QtQuick 2.0

Rectangle {
    id: rightNavBar

    property int choiceHeight: 70
    property color choiceBackgroundColor
    property color choiceSelectedBackgroundColor
    property string fontFamily: "Cambria Math"
    property string fontSize: "16"
    property color fontColor

    signal talentsClicked();
    signal equipmentClicked();
    signal buffsClicked();
    signal settingsClicked();

    width: 150

    state: "TALENTS"
    color: "transparent"

    RectangleBorders {
        id: chooseTalentsRect
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        rectColor: parent.state == "TALENTS" ? choiceSelectedBackgroundColor : choiceBackgroundColor

        height: choiceHeight

        Text {
            anchors.fill: parent

            text: "Talents"
            color: fontColor

            font {
                family: fontFamily
                pointSize: fontSize
            }

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        onRectangleClicked: {
            if (parent.state !== "TALENTS") {
                parent.state = "TALENTS"
                talentsClicked()
            }
        }
    }


    RectangleBorders {
        id: chooseGearRect
        anchors {
            top: chooseTalentsRect.bottom
            left: parent.left
            right: parent.right
        }

        rectColor: parent.state == "EQUIPMENT" ? choiceSelectedBackgroundColor : choiceBackgroundColor

        height: choiceHeight

        Text {
            anchors.fill: parent

            text: "Equipment"
            color: fontColor

            font {
                family: fontFamily
                pointSize: fontSize
            }

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        onRectangleClicked: {
            if (parent.state !== "EQUIPMENT") {
                parent.state = "EQUIPMENT"
                equipmentClicked()
            }
        }
    }

    RectangleBorders {
        id: chooseBuffsRect
        anchors {
            top: chooseGearRect.bottom
            left: parent.left
            right: parent.right
        }

        rectColor: parent.state == "BUFFS" ? choiceSelectedBackgroundColor : choiceBackgroundColor

        height: choiceHeight

        Text {
            anchors.fill: parent

            text: "Buffs"
            color: fontColor

            font {
                family: fontFamily
                pointSize: fontSize
            }

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        onRectangleClicked: {
            if (parent.state !== "BUFFS") {
                parent.state = "BUFFS"
                buffsClicked()
            }
        }
    }

    RectangleBorders {
        id: chooseFullSimSettingsRect
        anchors {
            top: chooseBuffsRect.bottom
            left: parent.left
            right: parent.right
        }

        rectColor: parent.state == "SETTINGS" ? choiceSelectedBackgroundColor : choiceBackgroundColor

        height: choiceHeight

        Text {
            anchors.fill: parent

            text: "Settings"
            color: fontColor

            font {
                family: fontFamily
                pointSize: fontSize
            }

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        onRectangleClicked: {
            if (parent.state !== "SETTINGS") {
                parent.state = "SETTINGS"
                settingsClicked()
            }
        }
    }

    RectangleBorders {
        id: characterStats
        anchors {
            top: chooseFullSimSettingsRect.bottom
            right: parent.right
            left:parent.left
        }

        rectColor: root.darkDarkGray

        height: 150

        Column {
            anchors {
                fill: parent
                leftMargin: 10
                topMargin: 10
            }

            Text {
                height: 15

                text: "Strength: " + character.strength
                color: "white"

                font {
                    family: fontFamily
                    pointSize: 10
                }

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                height: 15

                text: "Agility: " + character.agility
                color: "white"

                font {
                    family: fontFamily
                    pointSize: 10
                }

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                height: 15

                text: "Stamina: " + character.stamina
                color: "white"

                font {
                    family: fontFamily
                    pointSize: 10
                }

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                height: 15

                text: "Intellect: " + character.intellect
                color: "white"

                font {
                    family: fontFamily
                    pointSize: 10
                }

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                height: 15

                text: "Spirit: " + character.spirit
                color: "white"

                font {
                    family: fontFamily
                    pointSize: 10
                }

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                height: 15

                text: "Critical strike: " + character.critChance + "%"
                color: "white"

                font {
                    family: fontFamily
                    pointSize: 10
                }

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                height: 15

                text: "Hit: " + character.hitChance + "%"
                color: "white"

                font {
                    family: fontFamily
                    pointSize: 10
                }

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

    states: [
        State {
            name: "TALENTS"
        },
        State {
            name: "EQUIPMENT"
        },
        State {
            name: "BUFFS"
        },
        State {
            name: "SETTINGS"
        }]
}
