import QtQuick 2.0

Rectangle {
    property url talentTreeImage
    property string treePosition

    id: talentTreeRect

    height: parent.height
    width: parent.width

    Image {
        source: talentTreeImage
        height: parent.height
        width: parent.width
    }

//    Component.onCompleted: updateIcons()

//    function updateIcons() {
//        console.log("Position", position)
//        tier1LL.source = warrior.getIcon(treePosition, state)
//    }

    Column {
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
            right: parent.right
            topMargin: 5
            bottomMargin: 15
            leftMargin: 5
            rightMargin: 5
        }

        // tier 1
        Rectangle {
            height: parent.height / 7
            width: parent.width
            color: "transparent"

            Row {
                anchors.fill: parent

                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "1LL"
                }
                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "1ML"
                }
                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "1MR"
                }
                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "1RR"
                }
            }
        }
        // tier 2
        Rectangle {
            height: parent.height / 7
            width: parent.width
            color: "transparent"

            Row {
                anchors.fill: parent

                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "2LL"
                }
                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "2ML"
                }
                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "2MR"
                }
                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "2RR"
                }
            }
        }
        // tier 3
        Rectangle {
            height: parent.height / 7
            width: parent.width
            color: "transparent"

            Row {
                anchors.fill: parent

                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "3LL"
                }
                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "3ML"
                }
                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "3MR"
                }
                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "3RR"
                }
            }
        }
        // tier 4
        Rectangle {
            height: parent.height / 7
            width: parent.width
            color: "transparent"

            Row {
                anchors.fill: parent

                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "4LL"
                }
                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "4ML"
                }
                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "4MR"
                }
                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "4RR"
                }
            }
        }
        // tier 5
        Rectangle {
            height: parent.height / 7
            width: parent.width
            color: "transparent"

            Row {
                anchors.fill: parent

                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "5LL"
                }
                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "5ML"
                }
                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "5MR"
                }
                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "5RR"
                }
            }
        }
        // tier 6
        Rectangle {
            height: parent.height / 7
            width: parent.width
            color: "transparent"

            Row {
                anchors.fill: parent

                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "6LL"
                }
                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "6ML"
                }
                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "6MR"
                }
                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "6RR"
                }
            }
        }
        // tier 7
        Rectangle {
            height: parent.height / 7
            width: parent.width
            color: "transparent"

            Row {
                anchors.fill: parent

                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "7LL"
                }
                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "7ML"
                }
                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "7MR"
                }
                TalentBox {
                    height: parent.height
                    width: parent.width / 4
                    treePos: treePosition
                    talentPos: "7RR"
                }
            }
        }
    }
}
