import QtQuick 2.0
import EngineBreakdownSorting 1.0

RectangleBorders {
    height: 30
    width: parent.width

    Row {
        anchors.fill: parent

        property int percentageWidth: 120

        RectangleBorders {
            height: parent.height
            width: 200

            property int method: EngineBreakdownSorting.ByEvent

            onRectangleClicked: engineBreakdownModel.selectSort(method)
            onRectangleRightClicked: engineBreakdownModel.selectSort(method)

            rectColor: engineBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                              root.darkDarkGray

            TextSmall {
                text: "Event"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: EngineBreakdownSorting.ByPercentage

            onRectangleClicked: engineBreakdownModel.selectSort(method)
            onRectangleRightClicked: engineBreakdownModel.selectSort(method)

            rectColor: engineBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                              root.darkDarkGray

            TextSmall {
                text: "% of total"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: EngineBreakdownSorting.ByTotal

            onRectangleClicked: engineBreakdownModel.selectSort(method)
            onRectangleRightClicked: engineBreakdownModel.selectSort(method)

            rectColor: engineBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                              root.darkDarkGray

            TextSmall {
                text: "Total"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: EngineBreakdownSorting.ByHandledPerMin

            onRectangleClicked: engineBreakdownModel.selectSort(method)
            onRectangleRightClicked: engineBreakdownModel.selectSort(method)

            rectColor: engineBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                              root.darkDarkGray

            TextSmall {
                text: "Handled per minute"
            }
        }
    }
}
