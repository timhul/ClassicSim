import QtQuick 2.0
import ThreatBreakdownSorting 1.0

RectangleBorders {
    height: 30
    width: parent.width

    Row {
        anchors.fill: parent

        property int threatWidth : 80
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

            property int method: ThreatBreakdownSorting.ByName

            onRectangleClicked: threatBreakdownModel.selectSort(method)
            onRectangleRightClicked: threatBreakdownModel.selectSort(method)

            rectColor: threatBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Name"
            }
        }

        RectangleBorders {
            height: parent.height
            width: 120

            property int method: ThreatBreakdownSorting.ByTotalThreatAbsolute

            onRectangleClicked: threatBreakdownModel.selectSort(method)
            onRectangleRightClicked: threatBreakdownModel.selectSort(method)

            rectColor: threatBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Total Threat"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            property int method: ThreatBreakdownSorting.ByTotalThreatPercentage

            onRectangleClicked: threatBreakdownModel.selectSort(method)
            onRectangleRightClicked: threatBreakdownModel.selectSort(method)

            rectColor: threatBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Tot. Thrt %"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            property int method: ThreatBreakdownSorting.ByMinHitThrt

            onRectangleClicked: threatBreakdownModel.selectSort(method)
            onRectangleRightClicked: threatBreakdownModel.selectSort(method)

            rectColor: threatBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Min Hit"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            property int method: ThreatBreakdownSorting.ByAvgHitThrt

            onRectangleClicked: threatBreakdownModel.selectSort(method)
            onRectangleRightClicked: threatBreakdownModel.selectSort(method)

            rectColor: threatBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Avg Hit"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            property int method: ThreatBreakdownSorting.ByMaxHitThrt

            onRectangleClicked: threatBreakdownModel.selectSort(method)
            onRectangleRightClicked: threatBreakdownModel.selectSort(method)

            rectColor: threatBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Max Hit"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            property int method: ThreatBreakdownSorting.ByMinCritThrt

            onRectangleClicked: threatBreakdownModel.selectSort(method)
            onRectangleRightClicked: threatBreakdownModel.selectSort(method)

            rectColor: threatBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Min Crit"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            property int method: ThreatBreakdownSorting.ByAvgCritThrt

            onRectangleClicked: threatBreakdownModel.selectSort(method)
            onRectangleRightClicked: threatBreakdownModel.selectSort(method)

            rectColor: threatBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Avg Crit"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            property int method: ThreatBreakdownSorting.ByMaxCritThrt

            onRectangleClicked: threatBreakdownModel.selectSort(method)
            onRectangleRightClicked: threatBreakdownModel.selectSort(method)

            rectColor: threatBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Max Crit"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            property int method: ThreatBreakdownSorting.ByMinGlanceThrt

            onRectangleClicked: threatBreakdownModel.selectSort(method)
            onRectangleRightClicked: threatBreakdownModel.selectSort(method)

            rectColor: threatBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Min Glance"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            property int method: ThreatBreakdownSorting.ByAvgGlanceThrt

            onRectangleClicked: threatBreakdownModel.selectSort(method)
            onRectangleRightClicked: threatBreakdownModel.selectSort(method)

            rectColor: threatBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Avg Glance"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            property int method: ThreatBreakdownSorting.ByMaxGlanceThrt

            onRectangleClicked: threatBreakdownModel.selectSort(method)
            onRectangleRightClicked: threatBreakdownModel.selectSort(method)

            rectColor: threatBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Max Glance"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            property int method: ThreatBreakdownSorting.ByMinTPR

            onRectangleClicked: threatBreakdownModel.selectSort(method)
            onRectangleRightClicked: threatBreakdownModel.selectSort(method)

            rectColor: threatBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Min TPR"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            property int method: ThreatBreakdownSorting.ByAvgTPR

            onRectangleClicked: threatBreakdownModel.selectSort(method)
            onRectangleRightClicked: threatBreakdownModel.selectSort(method)

            rectColor: threatBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Avg TPR"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            property int method: ThreatBreakdownSorting.ByMaxTPR

            onRectangleClicked: threatBreakdownModel.selectSort(method)
            onRectangleRightClicked: threatBreakdownModel.selectSort(method)

            rectColor: threatBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Max TPR"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            property int method: ThreatBreakdownSorting.ByMinTPET

            onRectangleClicked: threatBreakdownModel.selectSort(method)
            onRectangleRightClicked: threatBreakdownModel.selectSort(method)

            rectColor: threatBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Min TPET"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            property int method: ThreatBreakdownSorting.ByAvgTPET

            onRectangleClicked: threatBreakdownModel.selectSort(method)
            onRectangleRightClicked: threatBreakdownModel.selectSort(method)

            rectColor: threatBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Avg TPET"
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            property int method: ThreatBreakdownSorting.ByMaxTPET

            onRectangleClicked: threatBreakdownModel.selectSort(method)
            onRectangleRightClicked: threatBreakdownModel.selectSort(method)

            rectColor: threatBreakdownModel.currentSortingMethod === method ? root.darkGray :
                                                                                   root.darkDarkGray

            TextSmall {
                text: "Max TPET"
            }
        }
    }
}
