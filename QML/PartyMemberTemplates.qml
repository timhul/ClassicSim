import QtQuick 2.0
import QtQuick.Controls 2.2

RectangleBorders {
    ScrollView {
        height: parent.height
        width: parent.width

        ListView {
            id: templateCharacters
            height: parent.height
            width: parent.width

            boundsBehavior: Flickable.StopAtBounds

            clip: true
            model: templateCharacterModel

            delegate: RectangleBorders {
                height: 40
                width: templateCharacters.width
                rectColor: _color
                property string title: _title
                onRectangleClicked: raid.selectTemplateCharacter(title)

                TextSmall {
                    color: "black"
                    text: parent.title
                }
            }
        }
    }
}
