import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    anchors.fill: parent

    property int settingDescWidth: 175

    color: "transparent"

    Column {
        anchors.fill: parent
        anchors.margins: 40
        spacing: 10

        Row {
            height: 30
            spacing: 5

            Text {
                text: "Iterations (full simulation)"
                height: 30
                width: settingDescWidth

                font {
                    family: "Arial"
                    pointSize: 9
                }
                color: "white"

                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
            }

            RectangleBorders {
                height: 30
                width: 100
                rectColor: root.darkGray

                onRectangleClicked: {
                    combatIterations.visible = true
                    combatIterations.forceActiveFocus()
                }

                Text {
                    text: settings.combatIterationsFullSim
                    visible: !combatIterations.visible
                    anchors.fill: parent

                    font {
                        family: "Arial"
                        pointSize: 9
                    }
                    color: "white"

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                TextField {
                    id: combatIterations
                    visible: false
                    anchors.fill: parent

                    validator: IntValidator {
                        id: combatIterationsValidator
                        bottom: 100;
                        top: 10000
                    }
                    inputMethodHints: Qt.ImhDigitsOnly
                    placeholderText: settings.combatIterationsFullSim

                    font {
                        family: "Arial"
                        pointSize: 9
                    }
                    color: "white"

                    onAccepted: {
                        settings.setCombatIterationsFullSim(text)
                        visible = false
                    }
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    background: Rectangle {
                        color: "transparent"
                    }
                }
            }

            Text {
                text: combatIterationsValidator.bottom + "-" + combatIterationsValidator.top
                height: 30
                width: 150

                font {
                    family: "Arial"
                    pointSize: 9
                }
                color: "white"

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }
        }


        Row {
            height: 30
            spacing: 5

            Text {
                text: "Combat length (full simulation)"
                height: 30
                width: settingDescWidth

                font {
                    family: "Arial"
                    pointSize: 9
                }
                color: "white"

                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
            }

            RectangleBorders {
                height: 30
                width: 100
                rectColor: root.darkGray

                onRectangleClicked: {
                    combatLength.visible = true
                    combatLength.forceActiveFocus()
                }

                Text {
                    text: settings.combatLength
                    visible: !combatLength.visible
                    anchors.fill: parent

                    font {
                        family: "Arial"
                        pointSize: 9
                    }
                    color: "white"

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                TextField {
                    id: combatLength
                    visible: false
                    anchors.fill: parent

                    validator: IntValidator {
                        id: combatLengthValidator
                        bottom: 30;
                        top: 600
                    }
                    inputMethodHints: Qt.ImhDigitsOnly
                    placeholderText: settings.combatLength

                    font {
                        family: "Arial"
                        pointSize: 9
                    }
                    color: "white"

                    onAccepted: {
                        settings.setCombatLength(text)
                        visible = false
                    }
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    background: Rectangle {
                        color: "transparent"
                    }
                }
            }

            Text {
                text: combatLengthValidator.bottom + "-" + combatLengthValidator.top + " seconds"
                height: 30
                width: 150

                font {
                    family: "Arial"
                    pointSize: 9
                }
                color: "white"

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }
        }

        Row {
            height: 30
            spacing: 5

            Text {
                text: "Active threads"
                height: 30
                width: settingDescWidth

                font {
                    family: "Arial"
                    pointSize: 9
                }
                color: "white"

                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
            }

            RectangleBorders {
                height: 30
                width: 100
                rectColor: root.darkGray

                onRectangleClicked: {
                    numThreads.visible = true
                    numThreads.forceActiveFocus()
                }

                Text {
                    text: settings.numThreads
                    visible: !numThreads.visible
                    anchors.fill: parent

                    font {
                        family: "Arial"
                        pointSize: 9
                    }
                    color: "white"

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                TextField {
                    id: numThreads
                    visible: false
                    anchors.fill: parent

                    validator: IntValidator {
                        id: numThreadsValidator
                        bottom: 1;
                        top: settings.maxThreads
                    }
                    inputMethodHints: Qt.ImhDigitsOnly
                    placeholderText: settings.numThreads

                    font {
                        family: "Arial"
                        pointSize: 9
                    }
                    color: "white"

                    onAccepted: {
                        settings.setNumThreads(text)
                        visible = false
                    }

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    background: Rectangle {
                        color: "transparent"
                    }
                }
            }

            Text {
                text: numThreadsValidator.bottom + "-" + numThreadsValidator.top
                height: 30
                width: 150

                font {
                    family: "Arial"
                    pointSize: 9
                }
                color: "white"

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }
        }
    }


}
