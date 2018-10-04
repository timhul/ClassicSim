import QtQuick 2.0
import WeaponSort 1.0

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

            onRectangleClicked: weaponModel.selectSort(WeaponSort.ByIlvl)
            onRectangleRightClicked: weaponModel.selectSort(WeaponSort.ByIlvl)

            rectColor: weaponModel.currentSortingMethod === WeaponSort.ByIlvl ? root.darkGray :
                                                                                root.darkDarkGray

            Text {
                text: "ILVL"

                font {
                    family: "Arial"
                    pointSize: 9
                }

                anchors.fill: parent

                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: 300

            onRectangleClicked: weaponModel.selectSort(WeaponSort.ByName)
            onRectangleRightClicked: weaponModel.selectSort(WeaponSort.ByName)

            rectColor: weaponModel.currentSortingMethod === WeaponSort.ByName ? root.darkGray :
                                                                                root.darkDarkGray

            Text {
                text: "Name"

                font {
                    family: "Arial"
                    pointSize: 9
                }

                anchors.fill: parent

                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: 50

            onRectangleClicked: weaponModel.selectSort(WeaponSort.ByDps)
            onRectangleRightClicked: weaponModel.selectSort(WeaponSort.ByDps)

            rectColor: weaponModel.currentSortingMethod === WeaponSort.ByDps ? root.darkGray :
                                                                               root.darkDarkGray

            Text {
                text: "DPS"

                font {
                    family: "Arial"
                    pointSize: 9
                }

                anchors.fill: parent

                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: 50

            onRectangleClicked: weaponModel.selectSort(WeaponSort.BySpeed)
            onRectangleRightClicked: weaponModel.selectSort(WeaponSort.BySpeed)

            rectColor: weaponModel.currentSortingMethod === WeaponSort.BySpeed ? root.darkGray :
                                                                                 root.darkDarkGray

            Text {
                text: "Speed"

                font {
                    family: "Arial"
                    pointSize: 9
                }

                anchors.fill: parent

                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: 50

            onRectangleClicked: weaponModel.selectSort(WeaponSort.ByPatch)
            onRectangleRightClicked: weaponModel.selectSort(WeaponSort.ByPatch)

            rectColor: weaponModel.currentSortingMethod === WeaponSort.ByPatch ? root.darkGray :
                                                                                 root.darkDarkGray

            Text {
                text: "Patch"

                font {
                    family: "Arial"
                    pointSize: 9
                }

                anchors.fill: parent

                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: 60

            onRectangleClicked: weaponModel.selectSort(WeaponSort.ByItemType)
            onRectangleRightClicked: weaponModel.selectSort(WeaponSort.ByItemType)

            rectColor: weaponModel.currentSortingMethod === WeaponSort.ByItemType ? root.darkGray :
                                                                                    root.darkDarkGray

            Text {
                text: "Type"

                font {
                    family: "Arial"
                    pointSize: 9
                }

                anchors.fill: parent

                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}
