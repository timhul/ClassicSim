import QtQuick 2.0
import QtQuick.Controls 2.2

RectangleBorders {
    height: parent.height
    width: 800

    Text {
        id: rotationName

        text: character.rotationInfoName

        width: parent.width
        height: 30

        elide: Text.ElideRight

        font {
            family: "Arial"
            pointSize: 12
        }

        color: "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: rotationDescription

        text: character.rotationInfoDesc
        width: parent.width

        anchors {
            top: rotationName.bottom
            topMargin: 10
            leftMargin: 40
            rightMargin: 40
        }

        font {
            family: "Arial"
            pointSize: 10
        }

        color: "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.WordWrap
    }

    RectangleBorders {
        width: parent.width
        anchors.top: rotationDescription.bottom
        anchors.bottom: parent.bottom

        ScrollView {
            anchors.fill: parent

            ListView {
                id: rotationConditions

                boundsBehavior: Flickable.StopAtBounds

                clip: true
                model: rotationConditionsModel

                delegate: RotationSpellConditions {
                    spellName: _name
                    spellIcon: _icon
                    spellConditions: _conditions
                }
            }
        }
    }
}
