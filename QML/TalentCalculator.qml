import QtQuick 2.0

Rectangle {
    color: root.darkGray
    height: width / 3 * 1.77 + 75
    width: parent.width

    Connections {
        target: talents
        onTalentsUpdated: {
            leftTotalPoints.text = talents.getTreePoints("LEFT")
            midTotalPoints.text = talents.getTreePoints("MID")
            rightTotalPoints.text = talents.getTreePoints("RIGHT")
        }
    }

    Column {
        anchors.fill: parent

        Row {
            height: 25
            width : parent.width

            Rectangle {
                height: parent.height
                width: parent.width

                color: "transparent"

                Text {
                    id: classText
                    anchors {
                        left: parent.left
                        leftMargin: 15
                    }

                    height: parent.height

                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter

                    color: character.classColor

                    font {
                        family: root.fontText
                        pointSize: 10
                    }

                    text: character.className
                }

                Text {
                    id: treeCombinationText
                    anchors {
                        left: classText.right
                        leftMargin: 5
                    }

                    height: parent.height

                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter

                    color: "white"

                    font {
                        family: root.fontText
                        pointSize: 10
                    }

                    text: leftTotalPoints.text + " / " + midTotalPoints.text + " / " + rightTotalPoints.text
                }

                Text {
                    anchors {
                        left: pointsLeftText.left
                        leftMargin: -120
                    }

                    height: parent.height

                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter

                    color: "white"

                    font {
                        family: root.fontText
                        pointSize: 10
                    }

                    text: talents.talentPointsRemaining < 51 ? "Required level: <b>" + (60 - talents.talentPointsRemaining) + "</b>" :
                                                               "Required level: <b>1</b>"
                }

                Text {
                    id: pointsLeftText
                    anchors {
                        left: parent.right
                        leftMargin: -100
                    }

                    height: parent.height

                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter

                    color: "white"

                    font {
                        family: root.fontText
                        pointSize: 10
                    }

                    text: "Points left: <b>" + talents.talentPointsRemaining + "</b>"
                }
            }

        }

        Row {
            height: width / 3 * 1.77
            width: parent.width - 1
            x: 1

            spacing: 1

            TalentTree {
                talentTreeImage: talents.leftTalentTreeBackground
                treePosition: "LEFT"
                y: 1
                z: 2
                height: parent.height - 2
                width: parent.width / 3 - 1
            }
            TalentTree {
                talentTreeImage: talents.midTalentTreeBackground
                treePosition: "MID"
                y: 1
                z: 1
                height: parent.height - 2
                width: parent.width / 3 - 1
            }
            TalentTree {
                talentTreeImage: talents.rightTalentTreeBackground
                treePosition: "RIGHT"
                y: 1
                z: 0
                height: parent.height - 2
                width: parent.width / 3 - 1
            }
        }

        Row {
            height: 50
            width : parent.width

            Rectangle {
                height: parent.height
                width: parent.width / 3

                color: "transparent"

                Text {
                    id: leftTotalPoints

                    anchors.centerIn: parent

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    color: root.gold

                    font {
                        family: root.fontNumbers
                        pointSize: 28
                    }

                    text:  talents.getTreePoints("LEFT")
                }

                ClickableImage {
                    onImageClicked: talents.clearTree("LEFT")
                }
            }

            Rectangle {
                height: parent.height
                width: parent.width / 3

                color: "transparent"

                Text {
                    id: midTotalPoints

                    anchors.centerIn: parent

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    color: root.gold

                    font {
                        family: root.fontNumbers
                        pointSize: 28
                    }

                    text:  talents.getTreePoints("MID")
                }

                ClickableImage {
                    onImageClicked: talents.clearTree("MID")
                }
            }

            Rectangle {
                height: parent.height
                width: parent.width / 3

                color: "transparent"
                Text {
                    id: rightTotalPoints

                    anchors.centerIn: parent

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    color: root.gold

                    font {
                        family: root.fontNumbers
                        pointSize: 28
                    }

                    text: talents.getTreePoints("RIGHT")
                }

                ClickableImage {
                    onImageClicked: talents.clearTree("RIGHT")
                }
            }
        }
    }
}
