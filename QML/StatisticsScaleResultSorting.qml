import QtQuick 2.0
import ScaleResultSorting 1.0

RectangleBorders {
    height: 30
    width: parent.width

    Row {
        anchors.fill: parent

        property int percentageWidth: 120

        RectangleBorders {
            height: parent.height
            width: 200

            property int method: ScaleResultSorting.ByName

            onRectangleClicked: scaleResultModel.selectSort(method)
            onRectangleRightClicked: scaleResultModel.selectSort(method)

            rectColor: scaleResultModel.currentSortingMethod === method ? root.darkGray :
                                                                          root.darkDarkGray

            TextSmall {
                text: "Option"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: ScaleResultSorting.ByAbsoluteValue

            onRectangleClicked: scaleResultModel.selectSort(method)
            onRectangleRightClicked: scaleResultModel.selectSort(method)

            rectColor: scaleResultModel.currentSortingMethod === method ? root.darkGray :
                                                                          root.darkDarkGray

            TextSmall {
                text: "Abs. value (DPS)"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: ScaleResultSorting.ByRelativeValue

            onRectangleClicked: scaleResultModel.selectSort(method)
            onRectangleRightClicked: scaleResultModel.selectSort(method)

            rectColor: scaleResultModel.currentSortingMethod === method ? root.darkGray :
                                                                          root.darkDarkGray

            TextSmall {
                text: "Rel. value (% DPS)"
            }
        }
    }
}
