import QtQuick 2.0

Rectangle {
    color: "transparent"

    property string outerBorderColorSelected: root.darkGray
    property string innerBorderColorSelected: "black"
    property color gradientRegularFrom: "#262626"
    property color gradientRegularTo: root.darkDarkGray
    property color gradientSelectedFrom
    property color gradientSelectedTo
    property bool selected
    property bool sendShiftClicks: false
    property bool sendCtrlClicks: false

    property int paddingInnerSelected: 1
    property int setRadiusSelected: 3

    signal selectButtonClicked()
    signal selectButtonRightClicked()
    signal selectButtonShiftClicked()
    signal selectButtonShiftRightClicked()
    signal selectButtonCtrlClicked()
    signal selectButtonCtrlRightClicked()

    radius: setRadiusSelected

    GradientButton {
        id: regular
        visible: !selected

        anchors.fill: parent

        outerBorderColor: outerBorderColorSelected
        innerBorderColor: innerBorderColorSelected
        setRadius: setRadiusSelected
        paddingInner: paddingInnerSelected
        gradientFrom: gradientRegularFrom
        gradientTo: gradientRegularTo
        sendShiftClick: sendShiftClicks
        sendCtrlClick: sendCtrlClicks

        onButtonClicked: selectButtonClicked()
        onButtonRightClicked: selectButtonRightClicked()
        onButtonShiftClicked: selectButtonShiftClicked()
        onButtonShiftRightClicked: selectButtonShiftRightClicked()
        onButtonCtrlClicked: selectButtonCtrlClicked()
        onButtonCtrlRightClicked: selectButtonCtrlRightClicked()
    }

    GradientButton {
        id: select
        visible: selected

        anchors.fill: parent

        outerBorderColor: outerBorderColorSelected
        innerBorderColor: innerBorderColorSelected
        setRadius: setRadiusSelected
        paddingInner: paddingInnerSelected
        gradientFrom: gradientSelectedFrom
        gradientTo: gradientSelectedTo
        sendShiftClick: sendShiftClicks
        sendCtrlClick: sendCtrlClicks

        onButtonClicked: selectButtonClicked()
        onButtonRightClicked: selectButtonRightClicked()
        onButtonShiftClicked: selectButtonShiftClicked()
        onButtonShiftRightClicked: selectButtonShiftRightClicked()
        onButtonCtrlClicked: selectButtonCtrlClicked()
        onButtonCtrlRightClicked: selectButtonCtrlRightClicked()
    }
}
