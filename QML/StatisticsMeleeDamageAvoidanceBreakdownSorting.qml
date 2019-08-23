import QtQuick 2.0
import MeleeDamageAvoidanceBreakdownSorting 1.0

RectangleBorders {
    height: 30
    width: parent.width

    Row {
        anchors.fill: parent

        property int attemptsWidth : 80
        property int percentageWidth: 70

        Rectangle {
            id: empty
            color: "transparent"
            width: 30
            height: parent.height
        }

        RectangleBorders {
            height: parent.height
            width: 200

            property int method: MeleeDamageAvoidanceBreakdownSorting.ByName

            onRectangleClicked: meleeAvoidanceBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeAvoidanceBreakdownModel.selectSort(method)

            rectColor: meleeAvoidanceBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                      root.darkDarkGray

            TextSmall {
                text: "Name"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.attemptsWidth

            property int method: MeleeDamageAvoidanceBreakdownSorting.ByTotalAttempts

            onRectangleClicked: meleeAvoidanceBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeAvoidanceBreakdownModel.selectSort(method)

            rectColor: meleeAvoidanceBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                      root.darkDarkGray

            TextSmall {
                text: "Tot. Attemps"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.attemptsWidth

            property int method: MeleeDamageAvoidanceBreakdownSorting.ByNumHits

            onRectangleClicked: meleeAvoidanceBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeAvoidanceBreakdownModel.selectSort(method)

            rectColor: meleeAvoidanceBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                      root.darkDarkGray

            TextSmall {
                text: "Hits"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: MeleeDamageAvoidanceBreakdownSorting.ByHitPercent

            onRectangleClicked: meleeAvoidanceBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeAvoidanceBreakdownModel.selectSort(method)

            rectColor: meleeAvoidanceBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                      root.darkDarkGray

            TextSmall {
                text: "Hit %"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.attemptsWidth

            property int method: MeleeDamageAvoidanceBreakdownSorting.ByNumCrits

            onRectangleClicked: meleeAvoidanceBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeAvoidanceBreakdownModel.selectSort(method)

            rectColor: meleeAvoidanceBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                      root.darkDarkGray

            TextSmall {
                text: "Crits"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: MeleeDamageAvoidanceBreakdownSorting.ByCritPercent

            onRectangleClicked: meleeAvoidanceBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeAvoidanceBreakdownModel.selectSort(method)

            rectColor: meleeAvoidanceBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                      root.darkDarkGray

            TextSmall {
                text: "Crit %"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.attemptsWidth

            property int method: MeleeDamageAvoidanceBreakdownSorting.ByNumGlances

            onRectangleClicked: meleeAvoidanceBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeAvoidanceBreakdownModel.selectSort(method)

            rectColor: meleeAvoidanceBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                      root.darkDarkGray

            TextSmall {
                text: "Glances"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: MeleeDamageAvoidanceBreakdownSorting.ByGlancePercent

            onRectangleClicked: meleeAvoidanceBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeAvoidanceBreakdownModel.selectSort(method)

            rectColor: meleeAvoidanceBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                      root.darkDarkGray

            TextSmall {
                text: "Glance %"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.attemptsWidth

            property int method: MeleeDamageAvoidanceBreakdownSorting.ByNumMisses

            onRectangleClicked: meleeAvoidanceBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeAvoidanceBreakdownModel.selectSort(method)

            rectColor: meleeAvoidanceBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                      root.darkDarkGray

            TextSmall {
                text: "Misses"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: MeleeDamageAvoidanceBreakdownSorting.ByMissPercent

            onRectangleClicked: meleeAvoidanceBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeAvoidanceBreakdownModel.selectSort(method)

            rectColor: meleeAvoidanceBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                      root.darkDarkGray

            TextSmall {
                text: "Miss %"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.attemptsWidth

            property int method: MeleeDamageAvoidanceBreakdownSorting.ByNumDodges

            onRectangleClicked: meleeAvoidanceBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeAvoidanceBreakdownModel.selectSort(method)

            rectColor: meleeAvoidanceBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                      root.darkDarkGray

            TextSmall {
                text: "Dodges"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: MeleeDamageAvoidanceBreakdownSorting.ByDodgePercent

            onRectangleClicked: meleeAvoidanceBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeAvoidanceBreakdownModel.selectSort(method)

            rectColor: meleeAvoidanceBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                      root.darkDarkGray

            TextSmall {
                text: "Dodge %"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.attemptsWidth

            property int method: MeleeDamageAvoidanceBreakdownSorting.ByNumParries

            onRectangleClicked: meleeAvoidanceBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeAvoidanceBreakdownModel.selectSort(method)

            rectColor: meleeAvoidanceBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                      root.darkDarkGray

            TextSmall {
                text: "Parries"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: MeleeDamageAvoidanceBreakdownSorting.ByParryPercent

            onRectangleClicked: meleeAvoidanceBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeAvoidanceBreakdownModel.selectSort(method)

            rectColor: meleeAvoidanceBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                      root.darkDarkGray

            TextSmall {
                text: "Parry %"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: MeleeDamageAvoidanceBreakdownSorting.ByNumPartial25

            onRectangleClicked: meleeAvoidanceBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeAvoidanceBreakdownModel.selectSort(method)

            rectColor: meleeAvoidanceBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                      root.darkDarkGray

            TextSmall {
                text: "Num R25%"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: MeleeDamageAvoidanceBreakdownSorting.ByPartial25Percent

            onRectangleClicked: meleeAvoidanceBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeAvoidanceBreakdownModel.selectSort(method)

            rectColor: meleeAvoidanceBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                      root.darkDarkGray

            TextSmall {
                text: "R25% %"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: MeleeDamageAvoidanceBreakdownSorting.ByNumPartial50

            onRectangleClicked: meleeAvoidanceBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeAvoidanceBreakdownModel.selectSort(method)

            rectColor: meleeAvoidanceBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                      root.darkDarkGray

            TextSmall {
                text: "Num R50%"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: MeleeDamageAvoidanceBreakdownSorting.ByPartial50Percent

            onRectangleClicked: meleeAvoidanceBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeAvoidanceBreakdownModel.selectSort(method)

            rectColor: meleeAvoidanceBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                      root.darkDarkGray

            TextSmall {
                text: "R50% %"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: MeleeDamageAvoidanceBreakdownSorting.ByNumPartial75

            onRectangleClicked: meleeAvoidanceBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeAvoidanceBreakdownModel.selectSort(method)

            rectColor: meleeAvoidanceBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                      root.darkDarkGray

            TextSmall {
                text: "Num R75%"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: MeleeDamageAvoidanceBreakdownSorting.ByPartial75Percent

            onRectangleClicked: meleeAvoidanceBreakdownModel.selectSort(method)
            onRectangleRightClicked: meleeAvoidanceBreakdownModel.selectSort(method)

            rectColor: meleeAvoidanceBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                      root.darkDarkGray

            TextSmall {
                text: "R75% %"
            }
        }
    }
}
