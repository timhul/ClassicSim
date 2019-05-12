import QtQuick 2.0

RectangleBorders {
    width: 425

    height: resetDefault.height + resetDefault.anchors.topMargin + textFieldEntries.children.length * (40)

    TextSmall {
        id: title
        anchorParent: false
        anchors {
            left: parent.left
            top: parent.top
            topMargin: 10
        }

        height: 25
        width: parent.width / 2

        pointSize: 11
        color: "lightgrey"

        text: "Simulation Settings"
    }

    GradientButton {
        id: resetDefault

        anchors {
            right: parent.right
            rightMargin: 10
            top: parent.top
            topMargin: 10
        }

        gradientFrom: root.wineRed
        gradientTo: root.darkRed

        height: 30
        width: 100
        TextSmall {
            text: "Reset defaults"
        }

        onButtonClicked: settings.resetDefaultSettings()
    }

    Column {
        id: textFieldEntries
        anchors.top: resetDefault.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

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

        SettingsTextFieldEntry {
            description: "Target armor"
            minVal: 0
            maxVal: 9999
            valueText: settings.targetBaseArmor
            placeholderText: settings.targetBaseArmor
            unitText: "armor (" + settings.targetArmor + ")"

            onAcceptedInput: settings.setTargetBaseArmor(value)
        }
    }
}
