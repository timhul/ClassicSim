import QtQuick 2.0

Rectangle {
    height: parent.height
    width: 850

    color: "transparent"

    RectangleBorders {
        id: filterRect
        anchors {
            left: parent.left
            top: parent.top
            leftMargin: 10
            topMargin: 10
        }

        width: 150
        height: 500

        ListView {
            interactive: false
            width: parent.width
            height: parent.height
            model: itemTypeFilterModel
            delegate: RectangleBorders {
                height: 30
                width: parent.width
                property bool filterActive: false
                rectColor: filterActive === true ? root.darkDarkGray : "#8c7400"

                Connections {
                    target: equipment
                    onFiltersUpdated: {
                        filterActive = equipment.getFilterActive(index)
                    }
                }

                onRectangleClicked: equipment.toggleSingleFilter(index)
                onRectangleRightClicked: equipment.toggleSingleFilter(index)

                Text {
                    anchors.fill: parent
                    text: desc

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

    Rectangle {
        id: itemsRect
        anchors {
            left: filterRect.right
            leftMargin: 10
            top: parent.top
            bottom: parent.bottom
            right: parent.right
        }

        color: "transparent"

        RectangleBorders {
            id: headerRect
            height: 60
            width: parent.width
        }

        RectangleBorders {
            id: selectionRect
            anchors {
                top: headerRect.bottom
                bottom: parent.bottom
                left: parent.left
                right: parent.right
            }
        }
    }
}
