import QtQuick 2.0

RectangleBorders {
    property string choiceText
    property string choiceState
    signal choiceClicked()

    height: parent.height / 3
    width: parent.width

    rectColor: parent.state === choiceState ? root.darkDarkGray : root.darkGray

    TextSmall {
        text: choiceText
        color: root.gold
        pointSize: 12
    }

    onRectangleClicked: {
        parent.state = choiceState
        choiceClicked()
    }
}
