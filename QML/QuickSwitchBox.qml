import QtQuick 2.0

RectangleBorders {
    property string choiceText
    property string choiceState
    signal choiceClicked()

    height: parent.height / 3
    width: parent.width

    rectColor: parent.state === choiceState ? root.darkDarkGray : root.darkGray

    Text {
        anchors.fill: parent

        text: choiceText
        color: root.gold

        font {
            family: root.fontText
            pointSize: 12
        }

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    onRectangleClicked: {
        parent.state = choiceState
        choiceClicked()
    }
}
