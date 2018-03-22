import QtQuick 2.0

Rectangle {
    property string outerBorderColor: "black"
    property string innerBorderColor: "gray"
    property color rectColor
    property int paddingInner: 1
    property string text: "Missing"

    signal rectangleClicked()

    color: "black"//outerBorderColor

    Rectangle {
        anchors {
            fill: parent
            margins: paddingInner
        }

        color: innerBorderColor


        Rectangle {
            anchors {
                fill: parent
                margins: paddingInner
            }

            color: outerBorderColor

            Rectangle {
                anchors {
                    fill: parent
                    margins:paddingInner
                }

                color: rectColor

                MouseArea {
                    anchors.fill: parent
                    onClicked: rectangleClicked()
                }
            }
        }
    }
}
