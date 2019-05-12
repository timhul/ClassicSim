import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    anchors.fill: parent

    color: "transparent"

    SettingsCommon {
        id: commonSettings

        anchors {
            top: parent.top
            topMargin: 20
            left: parent.left
            leftMargin: 20
        }
    }

    SettingsScaleFactors {
        id: scaleFactors

        anchors {
            top: parent.top
            topMargin: 20
            left: commonSettings.right
            leftMargin: 20
        }
    }
}
