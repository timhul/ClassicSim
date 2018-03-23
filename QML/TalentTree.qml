import QtQuick 2.0

Rectangle {
    property url talentTreeImage

    id: talentTreeRect

    height: parent.height
    width: parent.width

    Image {
        source: talentTreeImage
        height: parent.height
        width: parent.width
    }
}
