import QtQuick 2.0

RectangleBorders {
    height: parent.height
    width: 450

    Column {
        anchors.fill: parent
        anchors.margins: 5

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

        RectangleBorders {
            anchors {
                left: parent.left
                right: parent.right
                leftMargin: 50
                rightMargin: 50
            }

            height: 40

            Text {
                id: rotationDescription

                text: character.rotationInfoDesc

                anchors.fill: parent
                anchors.margins: 5

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
