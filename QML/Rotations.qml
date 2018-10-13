import QtQuick 2.0

Rectangle {
    height: parent.height * 0.9
    width: parent.width * 0.7
    color: root.darkDarkGray

    Row {
        anchors.fill: parent
        spacing: 10

        Column {
            width: 200
            height: parent.height
            spacing: 10

            RectangleBorders {
                width: parent.width
                height: 30

                onRectangleClicked: character.selectRotation()

                Text {
                    anchors {
                        fill: parent
                        leftMargin: 5
                        rightMargin: 5
                    }

                    text: "Select rotation"

                    font {
                        family: "Arial"
                        pointSize: 9
                    }

                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Text {
                anchors {
                    left: parent.left
                    right: parent.right
                    leftMargin: 5
                    rightMargin: 5
                }
                height: 45

                text: "Current: " + character.rotationName

                elide: Text.ElideRight

                font {
                    family: "Arial"
                    pointSize: 9
                }

                color: "white"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignTop
            }

            ListView {
                id: listView
                interactive: false
                width: parent.width
                implicitHeight: contentHeight

                model: rotationModel
                delegate: RectangleBorders {
                    height: 30
                    width: parent.width
                    rectColor: _selected === true ? "#8c7400" : root.darkDarkGray

                    onRectangleClicked:  character.selectInformationRotation(_index)

                    Text {
                        anchors {
                            fill: parent
                            leftMargin: 5
                            rightMargin: 5
                        }

                        text: _name

                        elide: Text.ElideRight

                        font {
                            family: "Arial"
                            pointSize: 9
                        }

                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }
        }

        RotationInformation {
        }
    }
}


