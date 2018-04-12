import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    height: parent.height
    width: parent.width

    color: root.darkDarkGray

    RectangleBorders {
        height: parent.height
        width: parent.width
        anchors {
            right: parent.right
        }

        color: root.darkGray

        ScrollView {
            height: parent.height * 0.9
            width: parent.width

            y: parent.height * 0.05

//            roles[NameRole] = "name";
//            roles[SpeedRole] = "speed";
//            roles[DpsRole] = "dps";
//            roles[PatchRole] = "patch";
//            roles[SourceRole] = "source";
//            roles[TypeRole] = "type";
//            roles[ReqLvlRole] = "req_lvl";
//            roles[ItemLvlRole] = "item_lvl";
//            roles[QualityRole] = "quality";
            ListView {
                model: weaponModel
                boundsBehavior: Flickable.StopAtBounds

                clip: true

                delegate: ItemEntryWeapon {
                    entryName: name
                    entrySpeed: speed
                    entryDps: dps
                    entryPatch: patch
                    entrySource: source
                    entryType: type
                    entryReq: req_lvl
                    entryItemlvl: item_lvl
                    entryQuality: quality
                }
            }
        }
    }
}
