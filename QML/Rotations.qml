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

            GradientButton {
                width: parent.width
                height: 30

                onButtonClicked: character.selectRotation()

                TextSmall {
                    anchorParent: false
                    anchors {
                        fill: parent
                        leftMargin: 5
                        rightMargin: 5
                    }

                    text: "Select rotation"
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
                delegate: GradientSelectedButton {
                    height: 30
                    width: parent.width

                    selected: _selected
                    gradientSelectedFrom: "#a88b01"
                    gradientSelectedTo: "#7a6500"

                    onSelectButtonClicked: character.selectInformationRotation(_index)

                    TextSmall {
                        anchorParent: false
                        anchors {
                            fill: parent
                            leftMargin: 5
                            rightMargin: 5
                        }

                        text: _name

                        elide: Text.ElideRight
                    }
                }
            }
        }

        RotationInformation {
        }
    }
}


