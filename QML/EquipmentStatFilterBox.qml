import QtQuick 2.0
import QtQuick.Controls 2.2

RectangleBorders {
    width: parent.width
    height: 30

    signal addFilter()

    Text {
        text: "Add stat filter"

        font {
            family: "Arial"
            pointSize: 9
        }

        anchors.fill: parent

        color: "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    onRectangleClicked: addFilter()

}
