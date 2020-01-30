import QtQuick 2.0
import QtQuick.Controls 2.1

ListView {
    id: list
    contentHeight: 120

    signal entryClicked(int affixId);

    clip: true
    focus: true
    flickableDirection: Flickable.VerticalFlick
    boundsBehavior: Flickable.StopAtBounds

    anchors.fill: parent
    highlight: Rectangle { color: "lightsteelblue"; radius: 5 }

    model: randomAffixModel
    delegate: RandomAffixDelegate {
        affixDescription: _descr
    }

    ScrollBar.vertical: ScrollBar {
        policy: ScrollBar.AlwaysOn
    }
}
