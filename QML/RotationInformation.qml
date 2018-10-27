import QtQuick 2.0

RectangleBorders {
    height: parent.height
    width: 450

    Column {
        anchors.fill: parent
        anchors.margins: 5

        spacing: 20

        Text {
            id: rotationName

            text: character.rotationInfoName

            width: parent.width
            height: 30

            elide: Text.ElideRight

            font {
                family: "Arial"
                pointSize: 12
            }

            color: "white"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: rotationDescription

            text: character.rotationInfoDesc
            width: parent.width

            anchors.margins: 40

            font {
                family: "Arial"
                pointSize: 10
            }

            color: "white"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
        }

        Text {
            id: underConstruction

            text: "UNDER CONSTRUCTION: Check Rotations/*.xml files meanwhile to see the details of each rotation."
            width: parent.width

            anchors.margins: 40

            font {
                family: "Arial"
                pointSize: 13
            }

            color: "gray"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
        }
    }
}
