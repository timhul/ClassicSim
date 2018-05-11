import QtQuick 2.0

Rectangle {
    id: classRect
    width: raceChoiceHeight * 4 + 10
    height: raceChoiceHeight * 2 + 2

    property int raceChoiceHeight: 55

    property url baseUrl: "Assets/races/Ui-charactercreate-races_"
    property string urlGender: "-female.png"
    property url urlDwarf: baseUrl + "dwarf" + urlGender
    property url urlGnome: baseUrl + "gnome" + urlGender
    property url urlHuman: baseUrl + "human" + urlGender
    property url urlNightElf: baseUrl + "nightelf" + urlGender
    property url urlOrc: baseUrl + "orc" + urlGender
    property url urlTauren: baseUrl + "tauren" + urlGender
    property url urlTroll: baseUrl + "troll" + urlGender
    property url urlUndead: baseUrl + "undead" + urlGender

    color: "transparent"

    Row {
        anchors.fill: parent

        visible: character.faction === root.alliance
        RaceChoiceBox {
            raceName: "Dwarf"
            raceIcon: urlDwarf
            sideLength: raceChoiceHeight
        }

        RaceChoiceBox {
            raceName: "Gnome"
            raceIcon: urlGnome
            sideLength: raceChoiceHeight
        }

        RaceChoiceBox {
            raceName: "Human"
            raceIcon: urlHuman
            sideLength: raceChoiceHeight
        }

        RaceChoiceBox {
            raceName: "NightElf"
            raceIcon: urlNightElf
            sideLength: raceChoiceHeight
        }
    }

    Row {
        anchors.fill: parent

        visible: character.faction === root.horde
        RaceChoiceBox {
            raceName: "Orc"
            raceIcon: urlOrc
            sideLength: raceChoiceHeight
        }

        RaceChoiceBox {
            raceName: "Tauren"
            raceIcon: urlTauren
            sideLength: raceChoiceHeight
        }

        RaceChoiceBox {
            raceName: "Troll"
            raceIcon: urlTroll
            sideLength: raceChoiceHeight
        }

        RaceChoiceBox {
            raceName: "Undead"
            raceIcon: urlUndead
            sideLength: raceChoiceHeight
        }
    }
}
