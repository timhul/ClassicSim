import QtQuick 2.0
import ItemSort 1.0

RectangleBorders {
    height: 60
    width: parent.width

    property int sortBoxHeight: 35
    property int sortBoxWidth: 100

    Row {
        height: parent.height
        width: parent.width - 3
        anchors {
            right: parent.right
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: 45

            onRectangleClicked: itemModel.selectSort(ItemSort.ByIlvl)
            onRectangleRightClicked: itemModel.selectSort(ItemSort.ByIlvl)

            rectColor: itemModel.currentSortingMethod === ItemSort.ByIlvl ? root.darkGray :
                                                                            root.darkDarkGray

            TextSmall {
                text: "ILVL"
            }
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: 300

            onRectangleClicked: itemModel.selectSort(ItemSort.ByName)
            onRectangleRightClicked: itemModel.selectSort(ItemSort.ByName)

            rectColor: itemModel.currentSortingMethod === ItemSort.ByName ? root.darkGray :
                                                                            root.darkDarkGray

            TextSmall {
                text: "Name"
            }
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: 100

            onRectangleClicked: itemModel.selectSort(ItemSort.ByPhase)
            onRectangleRightClicked: itemModel.selectSort(ItemSort.ByPhase)

            rectColor: itemModel.currentSortingMethod === ItemSort.ByPhase ? root.darkGray :
                                                                             root.darkDarkGray

            TextSmall {
                text: "Phase"
            }
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: 90

            onRectangleClicked: itemModel.selectSort(ItemSort.ByItemType)
            onRectangleRightClicked: itemModel.selectSort(ItemSort.ByItemType)

            rectColor: itemModel.currentSortingMethod === ItemSort.ByItemType ? root.darkGray :
                                                                                root.darkDarkGray

            TextSmall {
                text: "Type"
            }
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: 402

            rectColor: root.darkDarkGray

            TextSmall {
                text: "Source"
            }
        }
    }
}
