import QtQuick 2.0

Rectangle {
    height: parent.height
    width: parent.width

    color: root.darkDarkGray

    RectangleBorders {
        height: parent.height
        width: parent.width / 2
        anchors {
            right: parent.right
        }

        color: root.darkGray

        ListView {
            anchors.fill: parent

            model: itemModel

            delegate: Text {
                text: name

                color: "white"
            }
        }
    }
}
