import QtQuick 2.0

GradientSelectedButton {
    property string choiceText
    property string choiceState
    signal choiceClicked()

    height: parent.height / 3
    width: parent.width

    selected: parent.state === choiceState
    gradientSelectedFrom: "#4f4f4f"
    gradientSelectedTo: "#333333"

    TextSmall {
        text: choiceText
        color: "lightgray"
        pointSize: 12
    }

    onSelectButtonClicked: {
        parent.state = choiceState
        choiceClicked()
    }
    onSelectButtonRightClicked: {
        parent.state = choiceState
        choiceClicked()
    }
}
