import QtQuick 2.0

RectangleBorders {
    width: 300
    height: 30 * 5

    property int party

    function updatePartyMembers() {
        var info;
        for (var i = 0; i < partyColumn.children.length; ++i) {
            info = raid.partyMemberInfo(party, partyColumn.children[i].member)

            if (info["color"] !== undefined)
                partyColumn.children[i].rectColor = info["color"]
            else
                partyColumn.children[i].rectColor = root.darkGray

            if (info["text"] !== undefined)
                partyColumn.children[i].text = info["text"]
            else
                partyColumn.children[i].text = ""

            partyColumn.children[i].selected = info["selected"]
        }
    }

    Connections {
        target: raid
        function onPartyMembersUpdated() { updatePartyMembers() }
        function onSelectedPartyMemberChanged() { updatePartyMembers() }
    }

    Component.onCompleted: updatePartyMembers()

    TextSmall {
        anchorParent: false
        id: groupText
        text: "Group " + party
        height: 20
        width: parent.width
    }

    Column {
        id: partyColumn
        anchors {
            top: groupText.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        RectangleBorders {
            property int member: 1
            property string text
            property bool selected
            width: parent.width
            height: parent.height / 5

            outerBorderColor: selected ? "white" : root.darkGray

            onRectangleClicked: raid.selectPartyMember(party, member)
            onRectangleRightClicked: raid.clearPartyMember(party, member)

            TextSmall {
                text: parent.text
                color: "black"
            }
        }

        RectangleBorders {
            property int member: 2
            property string text
            property bool selected
            width: parent.width
            height: parent.height / 5

            outerBorderColor: selected ? "white" : root.darkGray

            onRectangleClicked: raid.selectPartyMember(party, member)
            onRectangleRightClicked: raid.clearPartyMember(party, member)

            TextSmall {
                text: parent.text
                color: "black"
            }
        }

        RectangleBorders {
            property int member: 3
            property string text
            property bool selected
            width: parent.width
            height: parent.height / 5

            outerBorderColor: selected ? "white" : root.darkGray

            onRectangleClicked: raid.selectPartyMember(party, member)
            onRectangleRightClicked: raid.clearPartyMember(party, member)

            TextSmall {
                text: parent.text
                color: "black"
            }
        }

        RectangleBorders {
            property int member: 4
            property string text
            property bool selected
            width: parent.width
            height: parent.height / 5

            outerBorderColor: selected ? "white" : root.darkGray

            onRectangleClicked: raid.selectPartyMember(party, member)
            onRectangleRightClicked: raid.clearPartyMember(party, member)

            TextSmall {
                text: parent.text
                color: "black"
            }
        }

        RectangleBorders {
            property int member: 5
            property string text
            property bool selected
            width: parent.width
            height: parent.height / 5

            outerBorderColor: selected ? "white" : root.darkGray

            onRectangleClicked: raid.selectPartyMember(party, member)
            onRectangleRightClicked: raid.clearPartyMember(party, member)

            TextSmall {
                text: parent.text
                color: "black"
            }
        }
    }
}
