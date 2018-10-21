import QtQuick 2.0
import DamageBreakdownSorting 1.0

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
            width: 125

            onRectangleClicked: damageBreakdownModel.selectSort(DamageBreakdownSorting.ByName)
            onRectangleRightClicked: damageBreakdownModel.selectSort(DamageBreakdownSorting.ByName)

            rectColor: damageBreakdownModel.currentSortingMethod === DamageBreakdownSorting.ByName ? root.darkGray :
                                                                                                     root.darkDarkGray

            TextSmall {
                text: "Name"
            }
        }

        RectangleBorders {
            height: parent.height
            width: 120

            onRectangleClicked: damageBreakdownModel.selectSort(DamageBreakdownSorting.ByTotalDamageAbsolute)
            onRectangleRightClicked: damageBreakdownModel.selectSort(DamageBreakdownSorting.ByTotalDamageAbsolute)

            rectColor: damageBreakdownModel.currentSortingMethod === DamageBreakdownSorting.ByTotalDamageAbsolute ? root.darkGray :
                                                                                                                    root.darkDarkGray

            TextSmall {
                text: "Total Damage"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            onRectangleClicked: damageBreakdownModel.selectSort(DamageBreakdownSorting.ByTotalDamagePercentage)
            onRectangleRightClicked: damageBreakdownModel.selectSort(DamageBreakdownSorting.ByTotalDamagePercentage)

            rectColor: damageBreakdownModel.currentSortingMethod === DamageBreakdownSorting.ByTotalDamagePercentage ? root.darkGray :
                                                                                                                      root.darkDarkGray

            TextSmall {
                text: "Tot. Dmg %"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.attemptsWidth

            property int method: DamageBreakdownSorting.ByTotalAttempts

            onRectangleClicked: damageBreakdownModel.selectSort(method)
            onRectangleRightClicked: damageBreakdownModel.selectSort(method)

            rectColor: damageBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                              root.darkDarkGray

            TextSmall {
                text: "Tot. Attemps"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.attemptsWidth

            property int method: DamageBreakdownSorting.ByNumHits

            onRectangleClicked: damageBreakdownModel.selectSort(method)
            onRectangleRightClicked: damageBreakdownModel.selectSort(method)

            rectColor: damageBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                              root.darkDarkGray

            TextSmall {
                text: "Hits"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: DamageBreakdownSorting.ByHitPercent

            onRectangleClicked: damageBreakdownModel.selectSort(method)
            onRectangleRightClicked: damageBreakdownModel.selectSort(method)

            rectColor: damageBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                              root.darkDarkGray

            TextSmall {
                text: "Hit %"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.attemptsWidth

            property int method: DamageBreakdownSorting.ByNumCrits

            onRectangleClicked: damageBreakdownModel.selectSort(method)
            onRectangleRightClicked: damageBreakdownModel.selectSort(method)

            rectColor: damageBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                              root.darkDarkGray

            TextSmall {
                text: "Crits"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: DamageBreakdownSorting.ByCritPercent

            onRectangleClicked: damageBreakdownModel.selectSort(method)
            onRectangleRightClicked: damageBreakdownModel.selectSort(method)

            rectColor: damageBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                              root.darkDarkGray

            TextSmall {
                text: "Crit %"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.attemptsWidth

            property int method: DamageBreakdownSorting.ByNumGlances

            onRectangleClicked: damageBreakdownModel.selectSort(method)
            onRectangleRightClicked: damageBreakdownModel.selectSort(method)

            rectColor: damageBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                              root.darkDarkGray

            TextSmall {
                text: "Glances"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: DamageBreakdownSorting.ByGlancePercent

            onRectangleClicked: damageBreakdownModel.selectSort(method)
            onRectangleRightClicked: damageBreakdownModel.selectSort(method)

            rectColor: damageBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                              root.darkDarkGray

            TextSmall {
                text: "Glance %"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.attemptsWidth

            property int method: DamageBreakdownSorting.ByNumMisses

            onRectangleClicked: damageBreakdownModel.selectSort(method)
            onRectangleRightClicked: damageBreakdownModel.selectSort(method)

            rectColor: damageBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                              root.darkDarkGray

            TextSmall {
                text: "Misses"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: DamageBreakdownSorting.ByMissPercent

            onRectangleClicked: damageBreakdownModel.selectSort(method)
            onRectangleRightClicked: damageBreakdownModel.selectSort(method)

            rectColor: damageBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                              root.darkDarkGray

            TextSmall {
                text: "Miss %"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.attemptsWidth

            property int method: DamageBreakdownSorting.ByNumDodges

            onRectangleClicked: damageBreakdownModel.selectSort(method)
            onRectangleRightClicked: damageBreakdownModel.selectSort(method)

            rectColor: damageBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                              root.darkDarkGray

            TextSmall {
                text: "Dodges"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: DamageBreakdownSorting.ByDodgePercent

            onRectangleClicked: damageBreakdownModel.selectSort(method)
            onRectangleRightClicked: damageBreakdownModel.selectSort(method)

            rectColor: damageBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                              root.darkDarkGray

            TextSmall {
                text: "Dodge %"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.attemptsWidth

            property int method: DamageBreakdownSorting.ByNumParries

            onRectangleClicked: damageBreakdownModel.selectSort(method)
            onRectangleRightClicked: damageBreakdownModel.selectSort(method)

            rectColor: damageBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                              root.darkDarkGray

            TextSmall {
                text: "Parries"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: DamageBreakdownSorting.ByParryPercent

            onRectangleClicked: damageBreakdownModel.selectSort(method)
            onRectangleRightClicked: damageBreakdownModel.selectSort(method)

            rectColor: damageBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                              root.darkDarkGray

            TextSmall {
                text: "Parry %"
            }
        }
    }
}
