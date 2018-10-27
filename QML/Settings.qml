import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    anchors.fill: parent

    color: "transparent"

    Column {
        anchors.fill: parent
        anchors.margins: 40
        spacing: 10

        SettingsTextFieldEntry {
            description: "Iterations (full simulation)"
            minVal: 100
            maxVal: 10000
            valueText: settings.combatIterationsFullSim
            placeholderText: settings.combatIterationsFullSim
            unitText: "iterations"

            onAcceptedInput: settings.setCombatIterationsFullSim(value)
        }

        SettingsTextFieldEntry {
            description: "Iterations (quick simulation)"
            minVal: 100
            maxVal: 10000
            valueText: settings.combatIterationsQuickSim
            placeholderText: settings.combatIterationsQuickSim
            unitText: "iterations"

            onAcceptedInput: settings.setCombatIterationsQuickSim(value)
        }

        SettingsTextFieldEntry {
            description: "Combat length"
            minVal: 30
            maxVal: 600
            valueText: settings.combatLength
            placeholderText: settings.combatLength
            unitText: "seconds"

            onAcceptedInput: settings.setCombatLength(value)
        }

        SettingsTextFieldEntry {
            description: "Active threads"
            minVal: 1
            maxVal: settings.maxThreads
            valueText: settings.numThreads
            placeholderText: settings.numThreads
            unitText: "threads"

            onAcceptedInput: settings.setNumThreads(value)
        }
    }
}
