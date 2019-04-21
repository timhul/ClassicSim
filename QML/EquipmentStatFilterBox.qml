import QtQuick 2.0
import QtQuick.Controls 2.2

RectangleBorders {
    property string filterText
    property int itemStatFlag
    property string comparator
    property int compareValue

    width: parent.width
    height: 60

    onRectangleRightClicked: activeStatFilterModel.removeFilter(itemStatFlag)

    Column {
        anchors.fill: parent

        TextSmall {
            text: filterText
            anchorParent: false

            height: parent.height / 2
            width: parent.width
        }

        Row {
            height: parent.height / 2
            width: parent.width

            RectangleBorders {
                height: parent.height
                width: parent.width / 2

                TextSmall {
                    text: comparator
                    pointSize: 13
                }

                onRectangleClicked: comparatorListView.visible = true
                onRectangleRightClicked: activeStatFilterModel.removeFilter(itemStatFlag)

                ListView {
                    id: comparatorListView
                    visible: false

                    height: comparatorModel.count * 30
                    width: parent.width

                    model: comparatorModel
                    boundsBehavior: Flickable.StopAtBounds

                    clip: true

                    delegate: RectangleBorders {
                        height: 30
                        width: parent.width
                        TextSmall {
                            text: comparatorText
                            pointSize: 12
                        }
                        onRectangleClicked: {
                            comparatorListView.visible = false
                            activeStatFilterModel.changeComparator(itemStatFlag, comparatorId)
                        }
                        onRectangleRightClicked: {
                            comparatorListView.visible = false
                        }
                    }
                }
            }

            RectangleBorders {
                height: parent.height
                width: parent.width / 2

                onRectangleClicked: {
                    statField.visible = true
                    statField.forceActiveFocus()
                }

                onRectangleRightClicked: activeStatFilterModel.removeFilter(itemStatFlag)

                TextSmall {
                    text: compareValue
                    visible: !statField.visible
                }

                TextField {
                    id: statField
                    visible: false
                    anchors.fill: parent

                    validator: IntValidator {
                        bottom: 0;
                        top: 999
                    }
                    inputMethodHints: Qt.ImhDigitsOnly
                    placeholderText: compareValue

                    font {
                        family: "Arial"
                        pointSize: 9
                    }
                    color: "white"

                    onAccepted: activeStatFilterModel.changeCompareValue(itemStatFlag, text)
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    background: Rectangle {
                        color: "transparent"
                    }
                }
            }
        }
    }

    ListModel {
        id: comparatorModel
        ListElement { comparatorId: 0; comparatorText: "<" }
        ListElement { comparatorId: 1; comparatorText: "<=" }
        ListElement { comparatorId: 2; comparatorText: "==" }
        ListElement { comparatorId: 3; comparatorText: ">" }
        ListElement { comparatorId: 4; comparatorText: ">=" }
    }
}
