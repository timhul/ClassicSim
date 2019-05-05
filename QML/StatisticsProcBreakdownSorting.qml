import QtQuick 2.0
import ProcBreakdownSorting 1.0

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

            property int method: ProcBreakdownSorting.ByName

            onRectangleClicked: procBreakdownModel.selectSort(method)
            onRectangleRightClicked: procBreakdownModel.selectSort(method)

            rectColor: procBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                            root.darkDarkGray

            TextSmall {
                text: "Name"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: ProcBreakdownSorting.ByAvgProcRate

            onRectangleClicked: procBreakdownModel.selectSort(method)
            onRectangleRightClicked: procBreakdownModel.selectSort(method)

            rectColor: procBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                            root.darkDarkGray

            TextSmall {
                text: "Avg Proc Rate %"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: ProcBreakdownSorting.ByEffectivePPM

            onRectangleClicked: procBreakdownModel.selectSort(method)
            onRectangleRightClicked: procBreakdownModel.selectSort(method)

            rectColor: procBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                            root.darkDarkGray

            TextSmall {
                text: "Effective PPM"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: ProcBreakdownSorting.ByNumProcs

            onRectangleClicked: procBreakdownModel.selectSort(method)
            onRectangleRightClicked: procBreakdownModel.selectSort(method)

            rectColor: procBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                            root.darkDarkGray

            TextSmall {
                text: "Num Procs"
            }
        }
    }
}
