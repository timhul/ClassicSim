import QtQuick 2.0
import QtGraphicalEffects 1.0

RectangleBorders {
    property string raceName
    property url raceIcon
    property int sideLength

    rectColor: "transparent"

    height: sideLength
    width: sideLength

    visible: character.raceAvailable(raceName)

    Connections {
        target: settings
        function onClassChanged() { visible = character.raceAvailable(raceName) }
    }

    Image {
        id: icon
        source: raceIcon
        anchors.fill: parent
    }

    Colorize {
        visible: character.raceName !== raceName
        anchors.fill: icon
        source: icon
        hue: 0.0
        saturation: 0.0
        lightness: 0.0
    }

    onRectangleClicked: character.selectRace(raceName)
    onRectangleRightClicked: character.selectRace(raceName)
}
