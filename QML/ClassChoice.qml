import QtQuick 2.0

Rectangle {
    id: classRect
    width: classChoiceHeight * 4 + 10
    height: classChoiceHeight * 2 + 2

    property int classChoiceHeight: 55

    property url baseUrl: "Assets/classes/Ui-charactercreate-classes_"
    property url urlDruid: baseUrl + "druid.png"
    property url urlHunter: baseUrl + "hunter.png"
    property url urlMage: baseUrl + "mage.png"
    property url urlPaladin: baseUrl + "paladin.png"
    property url urlPriest: baseUrl + "priest.png"
    property url urlShaman: baseUrl + "shaman.png"
    property url urlRogue: baseUrl + "rogue.png"
    property url urlWarlock: baseUrl + "warlock.png"
    property url urlWarrior: baseUrl + "warrior.png"

    color: "transparent"

    Column {
        anchors.fill: parent

        visible: character.faction === false

        Row {
            ClassChoiceBox {
                className: "Druid"
                classIcon: urlDruid
                sideLength: classChoiceHeight
            }

            ClassChoiceBox {
                className: "Hunter"
                classIcon: urlHunter
                sideLength: classChoiceHeight
            }

            ClassChoiceBox {
                className: "Mage"
                classIcon: urlMage
                sideLength: classChoiceHeight
            }

            ClassChoiceBox {
                className: "Paladin"
                classIcon: urlPaladin
                sideLength: classChoiceHeight
            }
        }

        Row {
            ClassChoiceBox {
                className: "Priest"
                classIcon: urlPriest
                sideLength: classChoiceHeight
            }

            ClassChoiceBox {
                className: "Rogue"
                classIcon: urlRogue
                sideLength: classChoiceHeight
            }

            ClassChoiceBox {
                className: "Warlock"
                classIcon: urlWarlock
                sideLength: classChoiceHeight
            }

            ClassChoiceBox {
                className: "Warrior"
                classIcon: urlWarrior
                sideLength: classChoiceHeight
            }
        }
    }

    Column {
        anchors.fill: parent

        visible: character.faction === true

        Row {
            ClassChoiceBox {
                className: "Druid"
                classIcon: urlDruid
                sideLength: classChoiceHeight
            }

            ClassChoiceBox {
                className: "Hunter"
                classIcon: urlHunter
                sideLength: classChoiceHeight
            }

            ClassChoiceBox {
                className: "Mage"
                classIcon: urlMage
                sideLength: classChoiceHeight
            }

            ClassChoiceBox {
                className: "Priest"
                classIcon: urlPriest
                sideLength: classChoiceHeight
            }
        }

        Row {
            ClassChoiceBox {
                className: "Shaman"
                classIcon: urlShaman
                sideLength: classChoiceHeight
            }

            ClassChoiceBox {
                className: "Rogue"
                classIcon: urlRogue
                sideLength: classChoiceHeight
            }

            ClassChoiceBox {
                className: "Warlock"
                classIcon: urlWarlock
                sideLength: classChoiceHeight
            }

            ClassChoiceBox {
                className: "Warrior"
                classIcon: urlWarrior
                sideLength: classChoiceHeight
            }
        }
    }
}
