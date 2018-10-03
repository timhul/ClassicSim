import QtQuick 2.0

Rectangle {
    property string outerBorderColor: root.darkGray
    property string innerBorderColor: "black"
    property color rectColor
    property color rectColorHighlighted: rectColor
    property bool sendShiftClick: false
    property bool sendCtrlClick: false
    property int paddingInner: 1
    property int setRadius: 0

    signal rectangleClicked()
    signal rectangleRightClicked()
    signal rectangleShiftClicked()
    signal rectangleShiftRightClicked()
    signal rectangleCtrlClicked()
    signal rectangleCtrlRightClicked()

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
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    anchors.fill: parent
                    onClicked: {
                        if (mouse.button === Qt.RightButton)
                            if (sendShiftClick && mouse.modifiers & Qt.ShiftModifier)
                                rectangleShiftRightClicked()
                            else if (sendCtrlClick && mouse.modifiers & Qt.ControlModifier)
                                rectangleCtrlRightClicked()
                            else
                                rectangleRightClicked()
                        else
                            if (sendShiftClick && mouse.modifiers & Qt.ShiftModifier)
                                rectangleShiftClicked()
                            else if (sendCtrlClick && mouse.modifiers & Qt.ControlModifier)
                                rectangleCtrlClicked()
                            else
                                rectangleClicked()
                    }
                }
            }
        }
    }
}
