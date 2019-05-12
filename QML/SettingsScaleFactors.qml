import QtQuick 2.0

RectangleBorders {
    width: 170
    height: title.height + title.anchors.topMargin + scaleModel.contentHeight + scaleModel.anchors.topMargin * 2

    TextSmall {
        id: title
        anchorParent: false
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            margins: 10
        }

        height: 20

        pointSize: 11
        color: "lightgrey"

        text: "Scale Factors"
    }

    ListView {
        id: scaleModel
        anchors {
            left: title.left
            top: title.bottom
            topMargin: 10
            bottom: parent.bottom
        }

        boundsBehavior: Flickable.StopAtBounds

        implicitHeight: contentHeight

        model: simScaleModel
        delegate: GradientSelectedButton {
            selected: _active
            gradientSelectedFrom: "#1b7500"
            gradientSelectedTo: "#134f00"

            height: 30
            width: 150
            TextSmall {
                text: _name
            }

            onSelectButtonClicked: simScaleModel.toggleOption(_enum)
        }
    }
}
