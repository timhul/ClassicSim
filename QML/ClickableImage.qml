import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    property string imageUrl: "Assets/cross.png"

    signal imageClicked();

    height: 40
    width: height

    y: parent.height / 2 - height / 2

    color: "transparent"

    anchors {
        right: parent.right
        rightMargin: 10
    }

    Image {
        id: image

        height: 25
        width: 25

        source: imageUrl

        y: parent.height / 2 - height / 2
        x: parent.width / 2 - width / 2
    }

    Colorize {
        id: hue
        visible: true
        anchors.fill: image
        source: image
        hue: 0.0
        saturation: 0.0
        lightness: 0.0
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onEntered: hue.visible = false
        onExited: hue.visible = true
        onClicked: imageClicked()
    }
}
