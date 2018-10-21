import QtQuick 2.0
import DamageBreakdownSorting 1.0

RectangleBorders {
    height: 30
    width: parent.width

    Row {
        anchors.fill: parent

        Rectangle {
            id: empty
            color: "transparent"
            width: 30
            height: parent.height
        }

        RectangleBorders {
            height: parent.height
            width: 125

            onRectangleClicked: damageBreakdownModel.selectSort(DamageBreakdownSorting.ByName)
            onRectangleRightClicked: damageBreakdownModel.selectSort(DamageBreakdownSorting.ByName)

            rectColor: damageBreakdownModel.currentSortingMethod === DamageBreakdownSorting.ByName ? root.darkGray :
                                                                                                     root.darkDarkGray

            TextSmall {
                text: "Name"
            }
        }

        RectangleBorders {
            height: parent.height
            width: 120

            onRectangleClicked: damageBreakdownModel.selectSort(DamageBreakdownSorting.ByTotalDamageAbsolute)
            onRectangleRightClicked: damageBreakdownModel.selectSort(DamageBreakdownSorting.ByTotalDamageAbsolute)

            rectColor: damageBreakdownModel.currentSortingMethod === DamageBreakdownSorting.ByTotalDamageAbsolute ? root.darkGray :
                                                                                                                    root.darkDarkGray

            TextSmall {
                text: "Total Damage"
            }
        }

        RectangleBorders {
            height: parent.height
            width: 75

            onRectangleClicked: damageBreakdownModel.selectSort(DamageBreakdownSorting.ByTotalDamagePercentage)
            onRectangleRightClicked: damageBreakdownModel.selectSort(DamageBreakdownSorting.ByTotalDamagePercentage)

            rectColor: damageBreakdownModel.currentSortingMethod === DamageBreakdownSorting.ByTotalDamagePercentage ? root.darkGray :
                                                                                                                      root.darkDarkGray

            TextSmall {
                text: "Total %"
            }
        }
    }
}
