import QtQuick 2.0

RectangleBorders {
    height: 500
    width: 150
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
                    filterActive = equipment.getFilterActive(item_type)
                }
            }

            onRectangleClicked: equipment.toggleSingleFilter(item_type)
            onRectangleRightClicked: equipment.toggleSingleFilter(item_type)

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
