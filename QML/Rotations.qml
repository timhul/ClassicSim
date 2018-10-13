import QtQuick 2.0

Rectangle {
    height: parent.height * 0.9
    width: parent.width * 0.7
    color: root.darkDarkGray

    Row {
        anchors.fill: parent
        spacing: 10

        ListView {
            id: listView
            interactive: false
            width: 200
            implicitHeight: contentHeight

            model: rotationModel
            delegate: RectangleBorders {
                height: 30
                width: parent.width
                rectColor: _selected === true ? "#8c7400" : root.darkDarkGray

                onRectangleClicked: character.selectRotation(_index)

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

        RotationInformation {
        }
    }
}


