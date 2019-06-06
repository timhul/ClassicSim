import QtQuick 2.0

Rectangle {
    color: "transparent"

    Column {
        anchors.fill: parent

        // Party 1-2
        Row {
            width: parent.width
            height: parent.height / 4

            PartyMembers {
                party: 1
                width: parent.width / 2
                height: parent.height
            }

            PartyMembers {
                party: 2
                width: parent.width / 2
                height: parent.height
            }
        }

        // Party 3-4
        Row {
            width: parent.width
            height: parent.height / 4

            PartyMembers {
                party: 3
                width: parent.width / 2
                height: parent.height
            }

            PartyMembers {
                party: 4
                width: parent.width / 2
                height: parent.height
            }
        }

        // Party 5-6
        Row {
            width: parent.width
            height: parent.height / 4

            PartyMembers {
                party: 5
                width: parent.width / 2
                height: parent.height
            }

            PartyMembers {
                party: 6
                width: parent.width / 2
                height: parent.height
            }
        }

        // Party 7-8
        Row {
            width: parent.width
            height: parent.height / 4

            PartyMembers {
                party: 7
                width: parent.width / 2
                height: parent.height
            }

            PartyMembers {
                party: 8
                width: parent.width / 2
                height: parent.height
            }
        }
    }
}
