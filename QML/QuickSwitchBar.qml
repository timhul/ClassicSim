import QtQuick 2.0

Rectangle {
    color: "transparent"

    Row {
        width: parent.width
        height: parent.height

        Column {
            width: 150
            height: parent.height

            state: "TALENT1"

            RectangleBorders {
                height: parent.height / 3
                width: parent.width

                rectColor: parent.state === "TALENT1" ? root.darkDarkGray : root.darkGray

                Text {
                    anchors.fill: parent

                    text: "Talent setup 1"
                    color: root.gold

                    font {
                        family: root.fontText
                        pointSize: 12
                    }

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                onRectangleClicked: {
                    parent.state = "TALENT1"
                    talents.setTalentSetup(0)
                }
            }

            RectangleBorders {
                height: parent.height / 3
                width: parent.width

                rectColor: parent.state === "TALENT2" ? root.darkDarkGray : root.darkGray

                Text {
                    anchors.fill: parent

                    text: "Talent setup 2"
                    color: root.gold

                    font {
                        family: root.fontText
                        pointSize: 12
                    }

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                onRectangleClicked: {
                    parent.state = "TALENT2"
                    talents.setTalentSetup(1)
                }
            }

            RectangleBorders {
                height: parent.height / 3
                width: parent.width

                rectColor: parent.state === "TALENT3" ? root.darkDarkGray : root.darkGray

                Text {
                    anchors.fill: parent

                    text: "Talent setup 3"
                    color: root.gold

                    font {
                        family: root.fontText
                        pointSize: 12
                    }

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                onRectangleClicked: {
                    parent.state = "TALENT3"
                    talents.setTalentSetup(2)
                }
            }
        }

        Column {
            width: 150
            height: parent.height

            state: "EQUIPMENT1"

            RectangleBorders {
                height: parent.height / 3
                width: parent.width

                rectColor: parent.state === "EQUIPMENT1" ? root.darkDarkGray : root.darkGray

                Text {
                    anchors.fill: parent

                    text: "Gear setup 1"
                    color: root.gold

                    font {
                        family: root.fontText
                        pointSize: 12
                    }

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                onRectangleClicked: {
                    parent.state = "EQUIPMENT1"
                    talents.setEquipmentSetup(0)
                }
            }

            RectangleBorders {
                height: parent.height / 3
                width: parent.width

                rectColor: parent.state === "EQUIPMENT2" ? root.darkDarkGray : root.darkGray

                Text {
                    anchors.fill: parent

                    text: "Gear setup 2"
                    color: root.gold

                    font {
                        family: root.fontText
                        pointSize: 12
                    }

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                onRectangleClicked: {
                    parent.state = "EQUIPMENT2"
                    talents.setEquipmentSetup(1)
                }
            }

            RectangleBorders {
                height: parent.height / 3
                width: parent.width

                rectColor: parent.state === "EQUIPMENT3" ? root.darkDarkGray : root.darkGray

                Text {
                    anchors.fill: parent

                    text: "Gear setup 3"
                    color: root.gold

                    font {
                        family: root.fontText
                        pointSize: 12
                    }

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                onRectangleClicked: {
                    parent.state = "EQUIPMENT3"
                    talents.setEquipmentSetup(2)
                }
            }
        }
    }
}
