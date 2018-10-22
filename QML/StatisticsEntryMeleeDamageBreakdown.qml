import QtQuick 2.0

Rectangle {
    width: 600
    height: 30

    color: "transparent"

    property url iconurl
    property string name
    property string totaldmgabsolute
    property string totaldmgpercentage
    property string minhit
    property string avghit
    property string maxhit
    property string mincrit
    property string avgcrit
    property string maxcrit
    property string minglance
    property string avgglance
    property string maxglance
    property string mindpr
    property string avgdpr
    property string maxdpr
    property string mindpet
    property string avgdpet
    property string maxdpet

    Row {
        anchors.fill: parent

        property int damageWidth: 80

        RectangleBorders {
            height: parent.height
            width: height

            Image {
                height: parent.height - 6
                width: height
                x: 3
                y: 3

                source: iconurl
            }
        }

        RectangleBorders {
            height: parent.height
            width: 200

            TextSmall {
                text: name
                anchors.leftMargin: 10

                horizontalAlignment: Text.AlignLeft
                wrapMode: Text.WordWrap
            }
        }

        RectangleBorders {
            height: parent.height
            width: 120

            TextSmall {
                text: totaldmgabsolute
            }
        }

        RectangleBorders {
            height: parent.height
            width: 70

            TextSmall {
                text: totaldmgpercentage
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.damageWidth

            TextSmall {
                text: minhit
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.damageWidth

            TextSmall {
                text: avghit
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.damageWidth

            TextSmall {
                text: maxhit
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.damageWidth

            TextSmall {
                text: mincrit
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.damageWidth

            TextSmall {
                text: avgcrit
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.damageWidth

            TextSmall {
                text: maxcrit
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.damageWidth

            TextSmall {
                text: minglance
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.damageWidth

            TextSmall {
                text: avgglance
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.damageWidth

            TextSmall {
                text: maxglance
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.damageWidth

            TextSmall {
                text: mindpr
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.damageWidth

            TextSmall {
                text: avgdpr
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.damageWidth

            TextSmall {
                text: maxdpr
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.damageWidth

            TextSmall {
                text: mindpet
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.damageWidth

            TextSmall {
                text: avgdpet
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.damageWidth

            TextSmall {
                text: maxdpet
            }
        }
    }
}
