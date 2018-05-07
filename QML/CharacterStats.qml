import QtQuick 2.0

RectangleBorders {
    property string fontFamily: root.fontText
    rectColor: root.darkDarkGray

    height: 175
    width: 150

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

        Text {
            height: 15

            text: "Attack Power: " + character.attackPower
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

            text: "MH Skill: " + character.wpnSkillMh
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

            text: "OH Skill: " + character.wpnSkillOh
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
