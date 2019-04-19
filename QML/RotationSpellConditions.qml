import QtQuick 2.0

RectangleBorders {
    property string spellName
    property url spellIcon
    property var spellConditions

    height: (spellConditionsText.implicitHeight + 10) > 45 ?
                (spellConditionsText.implicitHeight + 10) :
                45

    width: parent.width

    Image {
        id: spellIconImage
        source: spellIcon
        height: 35
        width: 35

        y: (parent.height - height) / 2

        x: 10
    }

    TextSmall {
        id: spellNameText
        width: 150

        pointSize: 11
        anchorParent: false

        anchors {
            left: spellIconImage.right
            leftMargin: 5
            top: parent.top
            bottom: parent.bottom
        }

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        text: spellName
    }

    TextSmall {
        id: spellConditionsText
        pointSize: 11
        anchorParent: false

        anchors {
            top: parent.top
            topMargin: 5
            left: spellNameText.right
            right: parent.right
            bottom: parent.bottom
            bottomMargin: 5
        }

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        text: spellConditions
    }
}
