import QtQuick 2.0

RectangleBorders {
    property string buffName
    property string buffIcon
    property string buffText
    property bool buffActive
    property bool isBuff: true
    property color selectedColor: "#173117"
    property color selectedHighlightColor: "#134f00"

    signal clearBuffsAndSelectSingle()
    signal selectRangeOfBuffs()
    signal toggleSingleBuff()

    height: 60
    width: 250

    rectColor: buffActive === true ? selectedColor : root.darkDarkGray
    rectColorHighlighted: buffActive === true ? selectedHighlightColor : root.darkGray
    outerBorderColor: root.darkGray
    sendShiftClick: true
    sendCtrlClick: true
    onRectangleClicked: clearBuffsAndSelectSingle()
    onRectangleRightClicked: clearBuffsAndSelectSingle()
    onRectangleShiftClicked: selectRangeOfBuffs()
    onRectangleShiftRightClicked: selectRangeOfBuffs()
    onRectangleCtrlClicked: toggleSingleBuff()
    onRectangleCtrlRightClicked: toggleSingleBuff()

    Row {
        id: row
        spacing: 10

        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
            right: parent.right
            leftMargin: 5
        }

        Image {
            id: icon
            height: 45
            width: height
            y: parent.height / 2 - height / 2

            source: buffIcon
        }

        TextSmall {
            text: buffText

            anchorParent: false

            width: row.width - icon.width - 20
            height: row.height

            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignLeft
        }
    }
}
