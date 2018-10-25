import QtQuick 2.0
import BuffBreakdownSorting 1.0

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

            property int method: BuffBreakdownSorting.ByName

            onRectangleClicked: buffBreakdownModel.selectSort(method)
            onRectangleRightClicked: buffBreakdownModel.selectSort(method)

            rectColor: buffBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                            root.darkDarkGray

            TextSmall {
                text: "Name"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: BuffBreakdownSorting.ByAvgUptime

            onRectangleClicked: buffBreakdownModel.selectSort(method)
            onRectangleRightClicked: buffBreakdownModel.selectSort(method)

            rectColor: buffBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                            root.darkDarkGray

            TextSmall {
                text: "Avg Uptime %"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: BuffBreakdownSorting.ByMinUptime

            onRectangleClicked: buffBreakdownModel.selectSort(method)
            onRectangleRightClicked: buffBreakdownModel.selectSort(method)

            rectColor: buffBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                            root.darkDarkGray

            TextSmall {
                text: "Min Uptime (s)"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: BuffBreakdownSorting.ByMaxUptime

            onRectangleClicked: buffBreakdownModel.selectSort(method)
            onRectangleRightClicked: buffBreakdownModel.selectSort(method)

            rectColor: buffBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                            root.darkDarkGray

            TextSmall {
                text: "Max Uptime (s)"
            }
        }
    }
}
