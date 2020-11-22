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
        delegate: GradientSelectedButton {
            height: 30
            width: 146
            x: 2
            gradientSelectedFrom: "#a88b01"
            gradientSelectedTo: "#7a6500"
            selected: true

            Connections {
                target: equipment
                function onFiltersUpdated() { selected = !equipment.getFilterActive(item_type) }
                function onEquipmentSlotSelected() { selected = !equipment.getFilterActive(item_type) }
            }

            sendShiftClicks: true
            sendCtrlClicks: true
            onSelectButtonClicked: equipment.clearFiltersAndSelectSingle(item_type)
            onSelectButtonRightClicked: equipment.clearFiltersAndSelectSingle(item_type)
            onSelectButtonShiftClicked: equipment.selectRangeOfFiltersFromPrevious(item_type)
            onSelectButtonShiftRightClicked: equipment.selectRangeOfFiltersFromPrevious(item_type)
            onSelectButtonCtrlClicked: equipment.toggleSingleFilter(item_type)
            onSelectButtonCtrlRightClicked: equipment.toggleSingleFilter(item_type)

            TextSmall {
                text: desc
            }
        }
    }

    GradientButton {
        id: addStatFilterButton
        height: 30

        anchors {
            top: listView.bottom
            topMargin: 15
            left: parent.left
            right: parent.right
        }

        TextSmall {
            text: "Add stat filter"
        }

        onButtonClicked: toggleStatFilterSelection()
        onButtonRightClicked: activeStatFilterModel.clearFilters()
    }

    ListView {
        id: activeStatFilterView

        anchors {
            top:  addStatFilterButton.bottom
            topMargin: 15
            left: parent.left
            right: parent.right
        }

        interactive: false
        implicitHeight: contentHeight

        model: activeStatFilterModel
        delegate: EquipmentStatFilterBox {
            filterText: _description
            itemStatFlag: _itemstatflag
            comparator: _comparator
            compareValue: _comparevalue
        }
    }
}
