import QtQuick 2.0

Rectangle {
    property string outerBorderColor: root.darkGray
    property string innerBorderColor: "black"
    property color gradientFrom: "#262626"
    property color gradientTo: root.darkDarkGray

    property int paddingInner: 1
    property int setRadius: 3
    property bool sendShiftClick: false
    property bool sendCtrlClick: false

    signal buttonClicked()
    signal buttonRightClicked()
    signal buttonShiftClicked()
    signal buttonShiftRightClicked()
    signal buttonCtrlClicked()
    signal buttonCtrlRightClicked()

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
                id: gradientRect

                anchors {
                    fill: parent
                    margins: paddingInner + 1
                }

                gradient: Gradient {
                    GradientStop {
                        position: 0.0
                        color: gradientFrom
                    }
                    GradientStop {
                        position: 1.0
                        color: gradientTo
                    }
                }

                radius: setRadius

                MouseArea {
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    anchors.fill: parent
                    onClicked: {
                        if (mouse.button === Qt.RightButton)
                            if (sendShiftClick && mouse.modifiers & Qt.ShiftModifier)
                                buttonShiftRightClicked()
                            else if (sendCtrlClick && mouse.modifiers & Qt.ControlModifier)
                                buttonCtrlRightClicked()
                            else
                                buttonRightClicked()
                        else
                            if (sendShiftClick && mouse.modifiers & Qt.ShiftModifier)
                                buttonShiftClicked()
                            else if (sendCtrlClick && mouse.modifiers & Qt.ControlModifier)
                                buttonCtrlClicked()
                            else
                                buttonClicked()
                    }
                }
            }
        }
    }
}
