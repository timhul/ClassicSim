import QtQuick 2.0
import QtQuick.Controls 2.2

Row {
    height: 30
    spacing: 5

    property string description
    property string valueText
    property string placeholderText
    property string unitText
    property int minVal
    property int maxVal

    signal acceptedInput(string value);

    Text {
        text: description
        height: 30
        width: 175

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
            textField.visible = true
            textField.forceActiveFocus()
        }

        Text {
            text: valueText
            visible: !textField.visible
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
            id: textField
            visible: false
            anchors.fill: parent

            validator: IntValidator {
                id: textFieldValidator
                bottom: minVal;
                top: maxVal
            }
            inputMethodHints: Qt.ImhDigitsOnly
            placeholderText: placeholderText

            font {
                family: "Arial"
                pointSize: 9
            }
            color: "white"

            onAccepted: {
                acceptedInput(text)
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
        text: textFieldValidator.bottom + "-" + textFieldValidator.top + " " + unitText
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
