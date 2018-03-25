import QtQuick 2.0

Rectangle {
    property string outerBorderColor: root.gray
    property string innerBorderColor: "black"
    property color rectColor
    property int paddingInner: 1
    property string text: "Missing"
    property int setRadius: 0

    signal rectangleClicked()

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
                    anchors.fill: parent
                    onClicked: rectangleClicked()
                }
            }
        }
    }
}
