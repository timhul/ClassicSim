import QtQuick 2.0

Rectangle {
    color: root.darkGray
    height: width / 3 * 1.77
    width: parent.width

    Row {
        anchors {
            fill: parent
            leftMargin: 1
        }

        spacing: 1

        TalentTree {
            talentTreeImage: "Assets/warrior/warrior_arms.jpg"
            treePosition: "LEFT"
            y: 1
            height: parent.height - 2
            width: parent.width / 3 - 1
        }

        TalentTree {
            talentTreeImage: "Assets/warrior/warrior_fury.jpg"
            treePosition: "MID"
            y: 1
            height: parent.height - 2
            width: parent.width / 3 - 1
        }

        TalentTree {
            talentTreeImage: "Assets/warrior/warrior_protection.jpg"
            treePosition: "RIGHT"
            y: 1
            height: parent.height - 2
            width: parent.width / 3 - 1
        }
    }
}
