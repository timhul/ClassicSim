import QtQuick 2.0
import MeleeDamageBreakdownSorting 1.0

RectangleBorders {
    height: 30
    width: parent.width

    Row {
        anchors.fill: parent

        property int damageWidth : 80
        property int percentageWidth: 70

        Rectangle {
            id: empty
            color: "transparent"
            width: 30
            height: parent.height
        }

        RectangleBorders {
            height: parent.height
            width: 125

            property int method: MeleeDamageBreakdownSorting.ByName

            onRectangleClicked: meleeDamageBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeDamageBreakdownModel.selectSort(method)

            rectColor: meleeDamageBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Name"
            }
        }

        RectangleBorders {
            height: parent.height
            width: 120

            property int method: MeleeDamageBreakdownSorting.ByTotalDamageAbsolute

            onRectangleClicked: meleeDamageBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeDamageBreakdownModel.selectSort(method)

            rectColor: meleeDamageBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Total Damage"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: MeleeDamageBreakdownSorting.ByTotalDamagePercentage

            onRectangleClicked: meleeDamageBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeDamageBreakdownModel.selectSort(method)

            rectColor: meleeDamageBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Tot. Dmg %"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.damageWidth

            property int method: MeleeDamageBreakdownSorting.ByMinHit

            onRectangleClicked: meleeDamageBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeDamageBreakdownModel.selectSort(method)

            rectColor: meleeDamageBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Min Hit"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.damageWidth

            property int method: MeleeDamageBreakdownSorting.ByAvgHit

            onRectangleClicked: meleeDamageBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeDamageBreakdownModel.selectSort(method)

            rectColor: meleeDamageBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Avg Hit"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.damageWidth

            property int method: MeleeDamageBreakdownSorting.ByMaxHit

            onRectangleClicked: meleeDamageBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeDamageBreakdownModel.selectSort(method)

            rectColor: meleeDamageBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Max Hit"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.damageWidth

            property int method: MeleeDamageBreakdownSorting.ByMinCrit

            onRectangleClicked: meleeDamageBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeDamageBreakdownModel.selectSort(method)

            rectColor: meleeDamageBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Min Crit"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.damageWidth

            property int method: MeleeDamageBreakdownSorting.ByAvgCrit

            onRectangleClicked: meleeDamageBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeDamageBreakdownModel.selectSort(method)

            rectColor: meleeDamageBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Avg Crit"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.damageWidth

            property int method: MeleeDamageBreakdownSorting.ByMaxCrit

            onRectangleClicked: meleeDamageBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeDamageBreakdownModel.selectSort(method)

            rectColor: meleeDamageBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                      root.darkDarkGray

            TextSmall {
                text: "Max Crit"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.damageWidth

            property int method: MeleeDamageBreakdownSorting.ByMinGlance

            onRectangleClicked: meleeDamageBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeDamageBreakdownModel.selectSort(method)

            rectColor: meleeDamageBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                      root.darkDarkGray

            TextSmall {
                text: "Min Glance"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.damageWidth

            property int method: MeleeDamageBreakdownSorting.ByAvgGlance

            onRectangleClicked: meleeDamageBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeDamageBreakdownModel.selectSort(method)

            rectColor: meleeDamageBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                      root.darkDarkGray

            TextSmall {
                text: "Avg Glance"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.damageWidth

            property int method: MeleeDamageBreakdownSorting.ByMaxGlance

            onRectangleClicked: meleeDamageBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeDamageBreakdownModel.selectSort(method)

            rectColor: meleeDamageBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                      root.darkDarkGray

            TextSmall {
                text: "Max Glance"
            }
        }
    }
}
