import QtQuick 2.0

RectangleBorders {
    property string name
    property bool selected
    property int index

    width: 200
    height: 30

    rectColor: selected ? "#232323" : root.darkDarkGray

    onRectangleClicked: rotationExecutorListModel.selectExecutor(index)

    TextSmall {
        text: name
        anchors.leftMargin: 10

        elide: Text.ElideRight
        horizontalAlignment: Text.AlignLeft
        wrapMode: Text.WordWrap
    }
}
