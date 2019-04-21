import QtQuick 2.0
import RotationExecutorBreakdownSorting 1.0

RectangleBorders {
    height: 30
    width: parent.width

    Row {
        anchors.fill: parent

        RectangleBorders {
            height: parent.height
            width: 200

            property int method: RotationExecutorBreakdownSorting.ByExecutor

            onRectangleClicked: rotationExecutorBreakdownModel.selectSort(method)
            onRectangleRightClicked: rotationExecutorBreakdownModel.selectSort(method)

            rectColor: rotationExecutorBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                        root.darkDarkGray

            TextSmall {
                text: "Executor Outcome"
            }
        }

        RectangleBorders {
            height: parent.height
            width: 200

            property int method: RotationExecutorBreakdownSorting.BySpellStatus

            onRectangleClicked: rotationExecutorBreakdownModel.selectSort(method)
            onRectangleRightClicked: rotationExecutorBreakdownModel.selectSort(method)

            rectColor: rotationExecutorBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                        root.darkDarkGray

            TextSmall {
                text: "Spell Status"
            }
        }

        RectangleBorders {
            height: parent.height
            width: 120

            property int method: RotationExecutorBreakdownSorting.ByValue

            onRectangleClicked: rotationExecutorBreakdownModel.selectSort(method)
            onRectangleRightClicked: rotationExecutorBreakdownModel.selectSort(method)

            rectColor: rotationExecutorBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                        root.darkDarkGray

            TextSmall {
                text: "Amount"
            }
        }
    }
}
