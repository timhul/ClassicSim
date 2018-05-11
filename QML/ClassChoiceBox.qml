import QtQuick 2.0
import QtGraphicalEffects 1.0

RectangleBorders {
    property string className
    property url classIcon
    property int sideLength

    rectColor: "transparent"

    height: sideLength
    width: sideLength

    Image {
        id: icon
        source: classIcon
        anchors.fill: parent
    }

    Colorize {
        visible: character.className !== className
        anchors.fill: icon
        source: icon
        hue: 0.0
        saturation: 0.0
        lightness: 0.0
    }

    onRectangleClicked: character.selectClass(className)
    onRectangleRightClicked: character.selectClass(className)
}
