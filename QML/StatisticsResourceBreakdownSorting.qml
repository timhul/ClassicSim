import QtQuick 2.0
import ResourceBreakdownSorting 1.0

RectangleBorders {
    height: 30
    width: parent.width

    Row {
        anchors.fill: parent

        property int percentageWidth: 120

        Rectangle {
            id: empty
            color: "transparent"
            width: 30
            height: parent.height
        }

        RectangleBorders {
            height: parent.height
            width: 200

            property int method: ResourceBreakdownSorting.ByName

            onRectangleClicked: resourceBreakdownModel.selectSort(method)
            onRectangleRightClicked: resourceBreakdownModel.selectSort(method)

            rectColor: resourceBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                root.darkDarkGray

            TextSmall {
                text: "Name"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: ResourceBreakdownSorting.ByRagePer5

            onRectangleClicked: resourceBreakdownModel.selectSort(method)
            onRectangleRightClicked: resourceBreakdownModel.selectSort(method)

            rectColor: resourceBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                root.darkDarkGray

            TextSmall {
                text: "Rage gain per 5s"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: ResourceBreakdownSorting.ByEnergyPer5

            onRectangleClicked: resourceBreakdownModel.selectSort(method)
            onRectangleRightClicked: resourceBreakdownModel.selectSort(method)

            rectColor: resourceBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                root.darkDarkGray

            TextSmall {
                text: "Energy gain per 5s"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: ResourceBreakdownSorting.ByManaPer5

            onRectangleClicked: resourceBreakdownModel.selectSort(method)
            onRectangleRightClicked: resourceBreakdownModel.selectSort(method)

            rectColor: resourceBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                root.darkDarkGray

            TextSmall {
                text: "Mana gain per 5s"
            }
        }
    }
}
