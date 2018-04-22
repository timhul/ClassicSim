import QtQuick 2.0

Rectangle {
    property string outerBorderColor: root.darkGray
    property string innerBorderColor: "black"
    property color rectColor
    property color rectColorHighlighted: rectColor
    property int paddingInner: 1
    property string text: "Missing"
    property int setRadius: 0

    signal rectangleClicked()
    signal rectangleRightClicked()

    color: "transparent"
    radius: setRadius

    Rectangle {
        anchors {
            fill: parent
            margins: paddingInner
        }

        color: "transparent"
        radius: setRadius
        border {
            width: paddingInner
            color: outerBorderColor
        }

        Rectangle {
            anchors {
                fill: parent
                margins: paddingInner
            }

            color: "transparent"
            radius: setRadius
            border {
                width: paddingInner
                color: innerBorderColor
            }

            Rectangle {
                anchors {
                    fill: parent
                    margins:paddingInner
                }

                color: rectColor
                radius: setRadius

                MouseArea {
                    hoverEnabled: true
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    anchors.fill: parent
                    onClicked: {
                        if (mouse.button === Qt.RightButton)
                            rectangleRightClicked()
                        else
                            rectangleClicked()
                    }
                    onEntered: parent.color = rectColorHighlighted
                    onExited: parent.color = rectColor
                }
            }
        }
    }
}
