import QtQuick 2.0

RectangleBorders {
    width: 150
    height: parent.height
    signal toggleStatFilterSelection();

    ListView {
        id: listView
        interactive: false
        width: parent.width
        implicitHeight: contentHeight

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
                onEquipmentSlotSelected: {
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

    RectangleBorders {
        anchors {
            top: listView.bottom
            topMargin: 15
            left: parent.left
            right: parent.right
        }

        height: 50

        EquipmentStatFilterBox {
            onAddFilter: toggleStatFilterSelection()
        }
    }
}
